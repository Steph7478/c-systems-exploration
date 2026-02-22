#include "routes.h"
#include "../../config/router/router.h"
#include "../controllers/controller.h"

void register_routes()
{
    router_add("GET", "/", home_handler);
    router_add("GET", "/users", users_handler);
}