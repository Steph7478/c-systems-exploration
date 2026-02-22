#include "response.h"
#include <stdio.h>
#include <string.h>

void response_init(HttpResponse *res, SOCKET client)
{
    res->client = client;
    res->status = 200;
}

void http_send_response(HttpResponse *res, const char *content_type, const char *body)
{
    char header_buffer[2048];
    int body_len = body ? (int)strlen(body) : 0;

    int n = sprintf(header_buffer,
                    "HTTP/1.1 %d OK\r\n"
                    "Content-Type: %s\r\n"
                    "Content-Length: %d\r\n"
                    "Server: MeuServidorC/1.0\r\n"
                    "Connection: close\r\n"
                    "\r\n",
                    res->status, content_type, body_len);

    send(res->client, header_buffer, n, 0);
    if (body_len > 0)
    {
        send(res->client, body, body_len, 0);
    }
}