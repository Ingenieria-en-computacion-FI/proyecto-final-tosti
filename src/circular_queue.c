#include <stdlib.h>
#include "circular_queue.h"

CircularQueue* cq_create(int capacity) {
    CircularQueue* q = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (q) {
        q->data = (int*)malloc(capacity * sizeof(int));
        q->capacity = capacity;
        q->front = 0;
        q->rear = -1;
        q->size = 0;
    }
    return q;
}

void cq_enqueue(CircularQueue* q, int value) {
    if (q->size == q->capacity) return; 
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
}

int cq_dequeue(CircularQueue* q) {
    if (q->size == 0) return -1; 
    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

void cq_destroy(CircularQueue* q) {
    if (q) {
        free(q->data);
        free(q);
    }
}