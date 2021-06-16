
/**
 * @file queue.h
 * @brief Implementation of queue data structure
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2021-06-08
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Queue API return type
 */
typedef enum queueRetType {
    QUEUE_NOERR  = 0,
    QUEUE_ERR    = -1,
    QUEUE_EMPTY  = -2,
    QUEUE_FULL   = -3
} QueueRetType;

/**
 * @brief Queue structure
 */
typedef struct queue {
    /* Index access members*/
    int front;
    int rear;

    /* Data relevent members*/
    void *data;
    unsigned int elemSize;
    unsigned int maxElem;
    unsigned int elemCount;
} Queue;

/* Function prototype */
static QueueRetType QueueInit(Queue **queue, unsigned int elemSize,
                              unsigned int maxElem);
static QueueRetType QueueDeinit(Queue *queue);

static QueueRetType Enqueue(Queue *queue, void *elem);
static QueueRetType Dequeue(Queue *queue, void *elem);
static QueueRetType QueuePeek(Queue *queue, void *elem);

static bool IsQueueEmpty(Queue *queue);
static bool IsQueueFull(Queue *queue);

/**
 * @brief Initializes queue context
 *
 * @param queue data structure
 * @param elemSize data size
 * @param maxElem maximum element in queue
 *
 * @return QueueRetType
 */
static QueueRetType
QueueInit(Queue **queue, unsigned int elemSize, unsigned int maxElem)
{
    *queue = calloc(1, sizeof(Queue));
    if (*queue == NULL) {
        return QUEUE_ERR;
    }

    (*queue)->data = calloc(maxElem, elemSize);
    if ((*queue)->data == NULL) {
        return QUEUE_ERR;
    }

    (*queue)->front     = (*queue)->rear = 0;
    (*queue)->maxElem   = maxElem;
    (*queue)->elemSize  = elemSize;
    (*queue)->elemCount = 0;

    return QUEUE_NOERR;
}

/**
 * @brief Enqueue element into queue
 *
 * @param queue data structure
 * @param elem data pointer to be pushed
 *
 * @return QueueRetType
 */
static QueueRetType
Enqueue(Queue *queue, void *elem)
{
    if (IsQueueFull(queue)) return QUEUE_FULL;

    memcpy(queue->data + (queue->rear * queue->elemSize), elem,
           queue->elemSize);
    queue->rear = (queue->rear + 1) % queue->maxElem;
    queue->elemCount++;

    return QUEUE_NOERR;
}

/**
 * @brief Dequeue element from queue
 *
 * @param queue data structure
 * @param elem data pointer where popped element is placed
 *
 * @return QueueRetType
 */
static QueueRetType
Dequeue(Queue *queue, void *elem)
{
    if (IsQueueEmpty(queue)) return QUEUE_EMPTY;

    memcpy(elem, queue->data + (queue->front * queue->elemSize),
           queue->elemSize);
    queue->front = (queue->front + 1) % queue->maxElem;
    queue->elemCount--;

    return QUEUE_NOERR;
}

/**
 * @brief Shows top element of queue
 *
 * @param queue ds
 * @param elem peeked element will be stored here
 *
 * @return QueueRetType
 */
static QueueRetType
QueuePeek(Queue *queue, void *elem)
{
    if (IsQueueEmpty(queue)) return QUEUE_EMPTY;

    memcpy(elem, queue->data + (queue->front * queue->elemSize),
           queue->elemSize);
    return QUEUE_NOERR;
}

/**
 * @brief Checks if queue is empty
 *
 * @param queue data structure
 *
 * @return true if queue is empty else false
 */
static bool
IsQueueEmpty(Queue *queue)
{
    return (queue->elemCount == 0);
}

/**
 * @brief Checks if queue is full
 *
 * @param queue data structure
 *
 * @return true if queue is full else false
 */
static bool
IsQueueFull(Queue *queue)
{
    return (queue->elemCount >= queue->maxElem);
}

/**
 * @brief Destroys queue data structure
 *
 * @param queue ds
 *
 * @return QueueRetType
 */
static QueueRetType
QueueDeinit(Queue *queue)
{
    free(queue->data);
    queue->data = NULL;
    free(queue);
    queue = NULL;

    return QUEUE_NOERR;
}

#endif /* __QUEUE_H__ */
