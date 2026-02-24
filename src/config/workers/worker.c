#include "worker.h"
#include "../http/http.h"
#include "../http/io/response.h"
#include "../http/io/request.h"
#include "../router/router.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>

extern ClientQueue clientQueue;
extern unsigned __int64 get_cpu_cycles();

DWORD WINAPI worker_thread(LPVOID param)
{
    (void)param;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

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

        unsigned __int64 q_cycles = exit_queue_timestamp - entry_timestamp;
        unsigned __int64 p_cycles = final_timestamp - exit_queue_timestamp;

        double q_ms = (double)(q_cycles * 1000) / frequency.QuadPart;
        double p_ms = (double)(p_cycles * 1000) / frequency.QuadPart;

        printf("[Metrics] Queue Latency: %.4f ms | Processing: %.4f ms\n", q_ms, p_ms);

        shutdown(c, SD_SEND);
        closesocket(c);
    }
    return 0;
}