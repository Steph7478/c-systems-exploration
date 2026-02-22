#ifndef REQUEST_H
#define REQUEST_H

#define MAX_HEADERS 20

typedef struct
{
    char key[64];
    char value[192];
} HttpHeader;

typedef struct
{
    char method[8];
    char path[256];
    char version[16];
} RequestLine;

typedef struct
{
    char *data;
    int content_length;
} RequestBody;

typedef struct
{
    RequestLine line;
    HttpHeader headers[MAX_HEADERS];
    int header_count;
    RequestBody body;
} HttpRequest;

#endif