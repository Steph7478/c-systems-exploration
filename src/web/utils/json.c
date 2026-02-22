#include "json.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    char *buf;
    size_t size;
    size_t capacity;
} Buffer;

static inline void buf_init(Buffer *b)
{
    b->capacity = 1024;
    b->size = 0;
    b->buf = (char *)malloc(b->capacity);
}

static inline void buf_grow(Buffer *b, size_t needed)
{
    size_t required = b->size + needed;
    if (required < b->capacity)
        return;

    while (b->capacity <= required)
        b->capacity <<= 1;

    b->buf = (char *)realloc(b->buf, b->capacity);
}

static inline void buf_write_char(Buffer *b, char c)
{
    buf_grow(b, 1);
    b->buf[b->size++] = c;
}

static inline void buf_write_raw(Buffer *b, const char *s, size_t len)
{
    buf_grow(b, len);
    memcpy(b->buf + b->size, s, len);
    b->size += len;
}

static inline void json_escape(Buffer *b, const char *s, size_t max_len)
{
    for (size_t i = 0; s[i] && i < max_len; i++)
    {
        switch (s[i])
        {
        case '"':
            buf_write_raw(b, "\\\"", 2);
            break;
        case '\\':
            buf_write_raw(b, "\\\\", 2);
            break;
        case '\n':
            buf_write_raw(b, "\\n", 2);
            break;
        case '\r':
            buf_write_raw(b, "\\r", 2);
            break;
        case '\t':
            buf_write_raw(b, "\\t", 2);
            break;
        default:
            buf_write_char(b, s[i]);
        }
    }
}

static inline void write_number(Buffer *b, JsonType type, void *ptr)
{
    char tmp[32];
    int len = 0;

    switch (type)
    {
    case JSON_INT:
        len = snprintf(tmp, sizeof(tmp), "%d", *(int *)ptr);
        break;
    case JSON_LONG:
        len = snprintf(tmp, sizeof(tmp), "%ld", *(long *)ptr);
        break;
    case JSON_FLOAT:
        len = snprintf(tmp, sizeof(tmp), "%g", *(float *)ptr);
        break;
    case JSON_DOUBLE:
        len = snprintf(tmp, sizeof(tmp), "%g", *(double *)ptr);
        break;
    case JSON_BOOL:
        if (*(int *)ptr)
            buf_write_raw(b, "true", 4);
        else
            buf_write_raw(b, "false", 5);
        return;
    default:
        return;
    }

    buf_write_raw(b, tmp, (size_t)len);
}

char *json_serialize_array(
    void *base,
    int count,
    size_t struct_size,
    JsonField *fields,
    int field_count)
{
    Buffer b;
    buf_init(&b);

    buf_write_char(&b, '[');

    for (int i = 0; i < count; i++)
    {
        char *obj = (char *)base + (i * struct_size);

        buf_write_char(&b, '{');

        for (int f = 0; f < field_count; f++)
        {
            JsonField *field = &fields[f];
            void *ptr = obj + field->offset;

            buf_write_char(&b, '"');
            buf_write_raw(&b, field->key, strlen(field->key));
            buf_write_raw(&b, "\":", 2);

            switch (field->type)
            {
            case JSON_STRING_PTR:
            {
                char *str = *(char **)ptr;
                if (!str)
                    break;
                buf_write_char(&b, '"');
                json_escape(&b, str, SIZE_MAX);
                buf_write_char(&b, '"');
                break;
            }

            case JSON_STRING_FIXED:
            {
                buf_write_char(&b, '"');
                json_escape(&b, (char *)ptr, field->size);
                buf_write_char(&b, '"');
                break;
            }

            default:
                write_number(&b, field->type, ptr);
            }

            if (f != field_count - 1)
                buf_write_char(&b, ',');
        }

        buf_write_char(&b, '}');

        if (i != count - 1)
            buf_write_char(&b, ',');
    }

    buf_write_char(&b, ']');
    buf_write_char(&b, '\0');

    return b.buf;
}