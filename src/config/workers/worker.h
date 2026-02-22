#ifndef WORKER_H
#define WORKER_H

#include "../queue/queue.h"

DWORD WINAPI worker_thread(LPVOID param);

#endif