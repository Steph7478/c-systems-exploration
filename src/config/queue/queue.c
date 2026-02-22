#include "queue.h"

void queue_init(ClientQueue *q)
{
    q->front = q->rear = 0;
    InitializeCriticalSection(&q->lock);
    InitializeConditionVariable(&q->cond);
}

void enqueue(ClientQueue *q, SOCKET c)
{
    EnterCriticalSection(&q->lock);
    q->queue[q->rear] = c;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    LeaveCriticalSection(&q->lock);
    WakeConditionVariable(&q->cond);
}

SOCKET dequeue(ClientQueue *q)
{
    EnterCriticalSection(&q->lock);
    while (q->front == q->rear)
        SleepConditionVariableCS(&q->cond, &q->lock, INFINITE);

    SOCKET c = q->queue[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    LeaveCriticalSection(&q->lock);
    return c;
}