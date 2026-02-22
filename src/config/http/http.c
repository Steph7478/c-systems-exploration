#include "http.h"
#include <string.h>
#include <stdlib.h>

int http_parse(SOCKET client, HttpRequest *req)
{
    char buf[2048];
    int n = recv(client, buf, sizeof(buf) - 1, 0);

    if (n <= 0)
        return 0;
    buf[n] = 0;

    char *body_ptr = strstr(buf, "\r\n\r\n");
    req->body.data = body_ptr ? body_ptr + 4 : NULL;

    return sscanf(buf, "%7s %255s %15s",
                  req->line.method,
                  req->line.path,
                  req->line.version) == 3;
}