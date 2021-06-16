
#include <stdio.h>
#include "queue.h"

int main()
{
    int a = 1, b = 2, c = 3, d = 4;
    int res = 0;
    Queue *queue = NULL;

    if (QueueInit(&queue, sizeof(int), 4) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to init queue\n");
        return -1;
    }

    if (Enqueue(queue, &a) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }
    if (Enqueue(queue, &b) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }

    if (Enqueue(queue, &c) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }
    if (Enqueue(queue, &d) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }

    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (QueuePeek(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to peek\n");
        return -1;
    }

    printf("Res: %d\n", res);
    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);

    if (IsQueueFull(queue) == true) {
        printf("Queue is full\n");
    }

    if (IsQueueEmpty(queue) == true) {
        printf("Queue is Empty\n");
    }

    if (Enqueue(queue, &a) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }
    if (Enqueue(queue, &b) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }
    if (Enqueue(queue, &c) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to enqueue\n");
        return -1;
    }
    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);
    if (Dequeue(queue, &res) != QUEUE_NOERR) {
        fprintf(stderr, "Failed to dequeue\n");
        return -1;
    }
    printf("Res: %d\n", res);
    QueueDeinit(queue);

    return 0;
}
