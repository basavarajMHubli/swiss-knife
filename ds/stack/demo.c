
#include <stdio.h>
#include "stack.h"

int main()
{
    int a = 1, b = 2, c = 3, d = 4;
    int res = 0;
    StackInfo stack;

    if (StackInit(&stack, sizeof(int), 3) != STACK_NOERR) {
        fprintf(stderr, "Failed to init stack\n");
        return -1;
    }

    if (StackPush(&stack, &a) != STACK_NOERR) {
        fprintf(stderr, "Failed to push stack\n");
        return -1;
    }
    if (StackPush(&stack, &b) != STACK_NOERR) {
        fprintf(stderr, "Failed to push stack\n");
        return -1;
    }
    if (StackPush(&stack, &c) != STACK_NOERR) {
        fprintf(stderr, "Failed to push stack\n");
        return -1;
    }
    if (StackPush(&stack, &d) != STACK_NOERR) {
        fprintf(stderr, "Failed to push stack\n");
    }

    if (StackPeek(&stack, &res) != STACK_NOERR) {
        fprintf(stderr, "Failed to pop stack\n");
        return -1;
    }
    printf("Peeked elem: %d\n", res);

    if (StackPop(&stack, &res) != STACK_NOERR) {
        fprintf(stderr, "Failed to pop stack\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (StackPop(&stack, &res) != STACK_NOERR) {
        fprintf(stderr, "Failed to pop stack\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (StackPop(&stack, &res) != STACK_NOERR) {
        fprintf(stderr, "Failed to pop stack\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (IsStackFull(&stack) == true) {
        printf("Stack is full\n");
    }

    if (IsStackEmpty(&stack) == true) {
        printf("Stack is Empty\n");
    }

    if (StackPop(&stack, &res) != STACK_NOERR) {
        fprintf(stderr, "Failed to pop stack\n");
        return -1;
    }
    printf("Res: %d\n", res);

    return 0;
}
