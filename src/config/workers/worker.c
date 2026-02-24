#include "worker.h"
#include "../http/http.h"
#include "../http/io/response.h"
#include "../http/io/request.h"
#include "../router/router.h"
#include <string.h>
#include <stdio.h>

extern ClientQueue clientQueue;
extern unsigned __int64 get_cpu_cycles();

DWORD WINAPI worker_thread(LPVOID param)
{
    (void)param;
    while (1)
    {
        unsigned __int64 entry_timestamp;
        SOCKET c = dequeue(&clientQueue, &entry_timestamp);

        if (c == INVALID_SOCKET)
            continue;

        unsigned __int64 exit_queue_timestamp = get_cpu_cycles();

        HttpRequest req = {0};
        if (http_parse(c, &req))
        {
            HttpResponse res;
            response_init(&res, c);
            router_handle(&req, &res);
        }

        unsigned __int64 final_timestamp = get_cpu_cycles();

        printf("[CPU Cycles] Queue Latency: %llu | Processing Time: %llu\n",
               exit_queue_timestamp - entry_timestamp,
               final_timestamp - exit_queue_timestamp);

        shutdown(c, SD_SEND);
        closesocket(c);
    }
    return 0;
}