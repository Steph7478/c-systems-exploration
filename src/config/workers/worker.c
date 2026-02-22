#include "worker.h"

#include "../http/http.h"
#include "../http/io/response.h"
#include "../http/io/request.h"
#include "../router/router.h"
#include <string.h>

extern ClientQueue clientQueue;

DWORD WINAPI worker_thread(LPVOID param)
{
    (void)param;
    while (1)
    {
        SOCKET c = dequeue(&clientQueue);
        if (c == INVALID_SOCKET)
            continue;

        HttpRequest req = {0};
        if (http_parse(c, &req))
        {
            HttpResponse res;
            response_init(&res, c);
            router_handle(&req, &res);
        }

        shutdown(c, SD_SEND);
        closesocket(c);
    }
    return 0;
}