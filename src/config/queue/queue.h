#ifndef QUEUE_H
#define QUEUE_H

#include "../../common/common.h"

typedef struct
{
    SOCKET socket;
    unsigned __int64 entry_cycles;
} ClientItem;

typedef struct
{
    ClientItem queue[QUEUE_SIZE];
    int front;
    int rear;
    CRITICAL_SECTION lock;
    CONDITION_VARIABLE cond;
} ClientQueue;

void queue_init(ClientQueue *q);
void enqueue(ClientQueue *q, SOCKET client, unsigned __int64 timestamp);
SOCKET dequeue(ClientQueue *q, unsigned __int64 *out_timestamp);

#endif