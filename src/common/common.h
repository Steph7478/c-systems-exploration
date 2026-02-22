#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define THREAD_COUNT 2
#define QUEUE_SIZE 64
#define MAX_ROUTES 32

#define CHECK(cond, msg, sock, cleanup)                          \
    do                                                           \
    {                                                            \
        if (!(cond))                                             \
        {                                                        \
            fprintf(stderr, "%s: %d\n", msg, WSAGetLastError()); \
            if (sock != INVALID_SOCKET)                          \
                closesocket(sock);                               \
            if (cleanup)                                         \
                WSACleanup();                                    \
            exit(1);                                             \
        }                                                        \
    } while (0)

#endif