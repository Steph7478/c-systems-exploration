#include "router.h"
#include <string.h>

static Route routes[MAX_ROUTES];
static int route_count = 0;

void router_add(const char *m, const char *p, RouteHandler h)
{
    if (route_count >= MAX_ROUTES)
        return;

    Route *r = &routes[route_count++];
    strncpy(r->method, m, 7);
    strncpy(r->path, p, 255);
    r->handler = h;
}

void router_handle(HttpRequest *req, HttpResponse *res)
{
    for (int i = 0; i < route_count; i++)
    {
        if (!strcmp(req->line.method, routes[i].method) &&
            !strcmp(req->line.path, routes[i].path))
        {
            routes[i].handler(req, res);
            return;
        }
    }
    res->status = 404;
    http_send_response(res, "text/html", "<h1>404 Not Found</h1>");
}