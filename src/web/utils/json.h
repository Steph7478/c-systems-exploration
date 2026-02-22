#ifndef JSON_H
#define JSON_H

#include <stddef.h>

typedef enum
{
    JSON_INT,
    JSON_LONG,
    JSON_DOUBLE,
    JSON_FLOAT,
    JSON_BOOL,
    JSON_STRING_PTR,
    JSON_STRING_FIXED
} JsonType;

typedef struct
{
    const char *key;
    size_t offset;
    JsonType type;
    size_t size;
} JsonField;

char *json_serialize_array(
    void *base,
    int count,
    size_t struct_size,
    JsonField *fields,
    int field_count);

#endif