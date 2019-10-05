
/**
 * @file stack.h
 * @brief Implementation of stack data structure
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2019-10-06
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Stack API return type
 */
typedef enum stackRetType {
    STACK_NOERR  = 0,
    STACK_ERR    = -1,
    STACK_EMPTY  = -2,
    STACK_FULL   = -3
} StackRetType;

/**
 * @brief Stack info structure
 */
typedef struct stackInfo {
    void *data;
    int topIdx;
    unsigned int elemSize;
    unsigned int maxElem;
} StackInfo;

/* Function prototype */
static inline StackRetType StackInit(StackInfo *stack, unsigned int elemSize,
                                     unsigned int maxElem);
static inline StackRetType StackDeinit(StackInfo *stack);

static inline StackRetType StackPush(StackInfo *stack, void *elem);
static inline StackRetType StackPop(StackInfo *stack, void *elem);
static inline StackRetType StackPeek(StackInfo *stack, void *elem);

static inline bool IsStackEmpty(StackInfo *stack);
static inline bool IsStackFull(StackInfo *stack);

/**
 * @brief Initializes stack context
 *
 * @param stack data structure
 * @param elemSize data size
 * @param maxElem maximum element in stack
 *
 * @return StackRetType
 */
static inline StackRetType
StackInit(StackInfo *stack, unsigned int elemSize, unsigned int maxElem)
{
    unsigned totalSize = elemSize * maxElem;
    stack->data = malloc(totalSize);
    if (stack->data == NULL) {
        return STACK_ERR;
    }

    memset(stack->data, 0, totalSize);
    stack->topIdx = -1;
    stack->maxElem = maxElem;
    stack->elemSize = elemSize;

    return STACK_NOERR;
}

/**
 * @brief Insert/Push element into stack
 *
 * @param stack data structure
 * @param elem data pointer to be pushed
 *
 * @return StackRetType
 */
static inline StackRetType
StackPush(StackInfo *stack, void *elem)
{
    if ((stack->topIdx + 1) == stack->maxElem) {
        return STACK_FULL;
    }

    stack->topIdx++;
    memcpy(stack->data + (stack->topIdx * stack->elemSize), elem,
           stack->elemSize);

    return STACK_NOERR;
}

/**
 * @brief Remove/Pop element from stack
 *
 * @param stack data structure
 * @param elem data pointer where popped element is placed
 *
 * @return StackRetType
 */
static inline StackRetType
StackPop(StackInfo *stack, void *elem)
{
    if (stack->topIdx == -1) {
        elem = NULL;
        return STACK_EMPTY;
    }

    memcpy(elem, stack->data + (stack->topIdx * stack->elemSize),
           stack->elemSize);
    stack->topIdx--;
    return STACK_NOERR;
}

/**
 * @brief Shows top element of stack
 *
 * @param stack
 * @param elem
 *
 * @return StackRetType
 */
static inline StackRetType
StackPeek(StackInfo *stack, void *elem)
{
    if (stack->topIdx == -1) {
        elem = NULL;
        return STACK_EMPTY;
    }

    memcpy(elem, stack->data + (stack->topIdx * stack->elemSize),
           stack->elemSize);
    return STACK_NOERR;
}

/**
 * @brief Checks if stack is empty
 *
 * @param stack data structure
 *
 * @return StackRetType
 */
static inline bool
IsStackEmpty(StackInfo *stack)
{
    return (stack->topIdx == -1);
}

/**
 * @brief Checks if stack is full
 *
 * @param stack data structure
 *
 * @return StackRetType
 */
static inline bool
IsStackFull(StackInfo *stack)
{
    return ((stack->topIdx + 1) == stack->maxElem);
}

/**
 * @brief Destroys stack data structure
 *
 * @param stack
 *
 * @return StackRetType
 */
static inline StackRetType
StackDeinit(StackInfo *stack)
{
    stack->topIdx = -1;
    stack->elemSize = 0;
    stack->maxElem = 0;
    free(stack->data);

    return STACK_NOERR;
}

#endif /* __STACK_H__ */
