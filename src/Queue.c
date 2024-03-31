/*
 * Queue.c
 *
 * Fixed-size generic array-based Queue implementation.
 *
 */

#include <stddef.h>
#include <stdlib.h>
#include "Queue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Queue module interface as documented in Queue.h.
 */


Queue *new_Queue(int maxSize) {
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->maxSize = maxSize;
    Q->front = -1;
    Q->rear = -1;
    Q->data = (void **)malloc(maxSize * sizeof(void *)); // void ** is a pointer to a pointer to void, this allows for a generic array and eliminates the need for type casting when dequeueing elements
    return Q;
}

bool Queue_enq(Queue* this, void* element) {
    if (this->front == 0 && this->rear==this->maxSize-1) {
        return false;
    } else if (this->front==-1) {
        return false;
    }
    return false;
}

void* Queue_deq(Queue* this) {
    return NULL;
}

int Queue_size(Queue* this) {
    return -1;
}

bool Queue_isEmpty(Queue* this) {
    return false;
}

void Queue_clear(Queue* this) {
}

void Queue_destroy(Queue* this) {
}
