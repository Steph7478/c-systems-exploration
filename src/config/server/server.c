#include "server.h"
#include "../../common/common.h"
#include "../queue/queue.h"
#include "../workers/worker.h"
#include "../../web/routes/routes.h"
#include "../http/http.h"
#include "../../web/controllers/controller.h"

ClientQueue clientQueue;

void start_server()
{
    WSADATA wsa;
    CHECK(WSAStartup(MAKEWORD(2, 2), &wsa) == 0, "WSAStartup failed", INVALID_SOCKET, 0);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    CHECK(sock != INVALID_SOCKET, "Socket failed", INVALID_SOCKET, 1);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(5000),
        .sin_addr.s_addr = INADDR_ANY};

    CHECK(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != SOCKET_ERROR, "Bind failed", sock, 1);

    listen(sock, SOMAXCONN);
    printf("Server running at http://localhost:5000\n");

    queue_init(&clientQueue);

    register_routes();

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        HANDLE h = CreateThread(NULL, 0, worker_thread, NULL, 0, NULL);
        if (h)
            CloseHandle(h);
    }

    while (1)
    {
        SOCKET client = accept(sock, NULL, NULL);
        if (client != INVALID_SOCKET)
        {
            enqueue(&clientQueue, client);
        }
    }
}