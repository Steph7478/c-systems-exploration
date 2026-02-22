#ifndef QUEUE_H
#define QUEUE_H
#include "../../common/common.h"

typedef struct
{
    SOCKET queue[QUEUE_SIZE];
    int front, rear;
    CRITICAL_SECTION lock;
    CONDITION_VARIABLE cond;
} ClientQueue;

void queue_init(ClientQueue *q);
void enqueue(ClientQueue *q, SOCKET client);
SOCKET dequeue(ClientQueue *q);
#endif
