#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../config/http/io/request.h"
#include "../../config/http/io/response.h"

void home_handler(HttpRequest *req, HttpResponse *res);
void users_handler(HttpRequest *req, HttpResponse *res);

#endif