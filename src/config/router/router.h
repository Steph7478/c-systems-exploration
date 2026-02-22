#ifndef ROUTER_H
#define ROUTER_H

#include "../http/io/request.h"
#include "../http/io/response.h"

#define MAX_ROUTES 32

typedef void (*RouteHandler)(HttpRequest *req, HttpResponse *res);

typedef struct
{
    char method[8];
    char path[256];
    RouteHandler handler;
} Route;

void router_add(const char *method, const char *path, RouteHandler handler);
void router_handle(HttpRequest *req, HttpResponse *res);

#endif