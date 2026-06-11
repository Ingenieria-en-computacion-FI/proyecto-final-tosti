#include <stdlib.h>
#include "memory_manager.h"

void coalesce_memory(MemoryBlock* head) {
    MemoryBlock* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            MemoryBlock* duplicate = current->next;
            current->size += duplicate->size;
            current->next = duplicate->next;
            if (duplicate->next != NULL) {
                duplicate->next->prev = current;
            }
            free(duplicate);
            continue; // Volver a validar con el nuevo adyacente
        }
        current = current->next;
    }
}

void mm_free(MemoryManager* mm, int start_address) {
    if (!mm) return;
    MemoryBlock* current = mm->head;
    while (current != NULL) {
        if (current->start == start_address) {
            current->free = 1;
            coalesce_memory(mm->head);
            return;
        }
        current = current->next;
    }
}
