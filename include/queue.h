#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* queue_create();
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void queue_destroy(Queue* queue);

#endif