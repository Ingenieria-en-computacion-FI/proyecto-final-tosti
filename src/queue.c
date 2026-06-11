#include <stdlib.h>
#include "queue.h"

Queue* queue_create() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}

void enqueue(Queue* queue, int value) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) return;
    newNode->data = value;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) return -1;
    QueueNode* temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return value;
}

void queue_destroy(Queue* queue) {
    while (queue->front != NULL) {
        dequeue(queue);
    }
    free(queue);
}