#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include "../../common/common.h"
#include "io\request.h"

int http_parse(SOCKET client, HttpRequest *req);

#endif