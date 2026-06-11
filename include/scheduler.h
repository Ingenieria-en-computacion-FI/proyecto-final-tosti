#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct ProcessNode {
    int pid;
    int burst_time;
    struct ProcessNode* next;
} ProcessNode;

typedef struct {
    ProcessNode* front;
    ProcessNode* rear;
} Scheduler;

Scheduler* scheduler_create_fifo();
void scheduler_add_process(Scheduler* scheduler, int pid, int burst_time);
int scheduler_next(Scheduler* scheduler);
void scheduler_destroy(Scheduler* scheduler);

#endif