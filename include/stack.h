#ifndef STACK_H
#define STACK_H

<<<<<<< HEAD
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;
=======
typedef struct Stack Stack;
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c

Stack* stack_create();
void stack_push(Stack* stack, int value);
int stack_pop(Stack* stack);
<<<<<<< HEAD
=======
int stack_peek(Stack* stack);
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
int stack_is_empty(Stack* stack);
void stack_destroy(Stack* stack);

#endif
