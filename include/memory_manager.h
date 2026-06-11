#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

typedef struct MemoryBlock {
<<<<<<< HEAD
    int start;
    int size;
    int free;
    struct MemoryBlock* next;
    struct MemoryBlock* prev;
} MemoryBlock;

typedef struct {
    MemoryBlock* head;
    int total_size;
} MemoryManager;

MemoryManager* mm_create(int size);
int mm_allocate_first_fit(MemoryManager* mm, int size);
void mm_free(MemoryManager* mm, int start_address);
void mm_destroy(MemoryManager* mm);
void coalesce_memory(MemoryBlock* head); // Auxiliar interna

#endif
=======

    int start;

    int size;

    int free;

    int pid;

    struct MemoryBlock* next;

    struct MemoryBlock* prev;

} MemoryBlock;

typedef struct MemoryManager {

    MemoryBlock* head;

    int total_memory;

} MemoryManager;

MemoryManager* mm_create(int total_memory);

int mm_allocate_first_fit(
    MemoryManager* mm,
    int size
);

void mm_free(
    MemoryManager* mm,
    int pid
);

void mm_coalesce(
    MemoryManager* mm
);

void mm_destroy(
    MemoryManager* mm
);

#endif
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
