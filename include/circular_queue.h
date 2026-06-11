#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
    int size;
} CircularQueue;

CircularQueue* cq_create(int capacity);
void cq_enqueue(CircularQueue* q, int value);
int cq_dequeue(CircularQueue* q);
void cq_destroy(CircularQueue* q);

#endif