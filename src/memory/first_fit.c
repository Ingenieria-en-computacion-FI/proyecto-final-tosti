#include <stdlib.h>
#include "memory_manager.h"

MemoryManager* mm_create(int size) {
    MemoryManager* mm = (MemoryManager*)malloc(sizeof(MemoryManager));
    if (mm) {
        mm->total_size = size;
        mm->head = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        if (mm->head) {
            mm->head->start = 0;
            mm->head->size = size;
            mm->head->free = 1;
            mm->head->next = NULL;
            mm->head->prev = NULL;
        }
    }
    return mm;
}

int mm_allocate_first_fit(MemoryManager* mm, int size) {
    MemoryBlock* current = mm->head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size) {
                // Fragmentación interna del bloque
                MemoryBlock* leftover = (MemoryBlock*)malloc(sizeof(MemoryBlock));
                if (!leftover) return -1;
                leftover->start = current->start + size;
                leftover->size = current->size - size;
                leftover->free = 1;
                
                leftover->next = current->next;
                leftover->prev = current;
                if (current->next != NULL) {
                    current->next->prev = leftover;
                }
                current->next = leftover;
                current->size = size;
            }
            current->free = 0;
            return current->start; // Retorna la dirección base
        }
        current = current->next;
    }
    return -1; // Memoria insuficiente
}

void mm_destroy(MemoryManager* mm) {
    if (!mm) return;
    MemoryBlock* current = mm->head;
    while (current != NULL) {
        MemoryBlock* next = current->next;
        free(current);
        current = next;
    }
    free(mm);
}
