#include <stdlib.h>
#include "scheduler.h"

Scheduler* scheduler_create_fifo() {
    Scheduler* s = (Scheduler*)malloc(sizeof(Scheduler));
    if (s) {
        s->front = NULL;
        s->rear = NULL;
    }
    return s;
}

void scheduler_add_process(Scheduler* scheduler, int pid, int burst_time) {
    ProcessNode* newNode = (ProcessNode*)malloc(sizeof(ProcessNode));
    if (!newNode) return;
    newNode->pid = pid;
    newNode->burst_time = burst_time;
    newNode->next = NULL;

    if (scheduler->rear == NULL) {
        scheduler->front = newNode;
        scheduler->rear = newNode;
    } else {
        scheduler->rear->next = newNode;
        scheduler->rear = newNode;
    }
}

int scheduler_next(Scheduler* scheduler) {
    if (scheduler->front == NULL) return -1;
    ProcessNode* temp = scheduler->front;
    int pid = temp->pid;
    scheduler->front = scheduler->front->next;
    if (scheduler->front == NULL) {
        scheduler->rear = NULL;
    }
    free(temp);
    return pid;
}

void scheduler_destroy(Scheduler* scheduler) {
    while (scheduler->front != NULL) {
        scheduler_next(scheduler);
    }
    free(scheduler);
}