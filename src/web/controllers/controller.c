#include "controller.h"
#include <string.h>
#include "../services/user_service.h"
#include "../utils/json.h"

void home_handler(HttpRequest *req, HttpResponse *res)
{
    res->status = 200;
    http_send_response(res, "text/html", "<h1>You got me!</h1>");
}

void users_handler(HttpRequest *req, HttpResponse *res)
{
    char *json_response = user_get_all_as_json();

    if (json_response == NULL)
    {
        res->status = 500;
        http_send_response(res, "text/plain", "Memory error");
        return;
    }

    res->status = 200;
    http_send_response(res, "application/json", json_response);

    free(json_response);
}