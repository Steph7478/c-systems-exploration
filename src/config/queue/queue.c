#include "queue.h"

void queue_init(ClientQueue *q)
{
    q->front = q->rear = 0;
    InitializeCriticalSection(&q->lock);
    InitializeConditionVariable(&q->cond);
}

void enqueue(ClientQueue *q, SOCKET c, unsigned __int64 timestamp)
{
    EnterCriticalSection(&q->lock);

    q->queue[q->rear].socket = c;
    q->queue[q->rear].entry_cycles = timestamp;
    q->rear = (q->rear + 1) % QUEUE_SIZE;

    LeaveCriticalSection(&q->lock);
    WakeConditionVariable(&q->cond);
}

SOCKET dequeue(ClientQueue *q, unsigned __int64 *out_timestamp)
{
    EnterCriticalSection(&q->lock);
    while (q->front == q->rear)
        SleepConditionVariableCS(&q->cond, &q->lock, INFINITE);

    ClientItem item = q->queue[q->front];
    if (out_timestamp)
        *out_timestamp = item.entry_cycles;

    q->front = (q->front + 1) % QUEUE_SIZE;

    LeaveCriticalSection(&q->lock);
    return item.socket;
}