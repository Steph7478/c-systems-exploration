#ifndef RESPONSE_H
#define RESPONSE_H

#include "../../../common/common.h"

typedef struct
{
    SOCKET client;
    int status;
    char *content_type;
} HttpResponse;

void response_init(HttpResponse *res, SOCKET client);
void http_send_response(HttpResponse *res, const char *content_type, const char *body);

#endif