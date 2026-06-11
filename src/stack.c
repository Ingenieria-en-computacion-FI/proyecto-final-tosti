#include <stdlib.h>
#include "stack.h"

Stack* stack_create() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) stack->top = NULL;
    return stack;
}

void stack_push(Stack* stack, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return;
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) return -1;
    StackNode* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    return value;
}

int stack_is_empty(Stack* stack) {
    return stack->top == NULL;
}

void stack_destroy(Stack* stack) {
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}