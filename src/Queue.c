/*
 * Queue.c
 *
 * Fixed-size generic array-based Queue implementation.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Queue module interface as documented in Queue.h.
 */


Queue *new_Queue(int max_size) {
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->max_size = max_size+1; // one extra space to distinguish between full and empty
    Q->size = 0; // current size
    Q->head = 0; // write index
    Q->tail = 0; // read index
    Q->data = (void **)malloc(Q->max_size * sizeof(void *));
    return Q;
}
/*
void ** is a pointer to a pointer to void, this allows for a generic array and eliminates the need for type casting when dequeueing elements

calloc not only allocates the memory but also initializes all bytes in the allocated storage to zero. 
This is particularly useful when you're dealing with data structures as it ensures all fields are zeroed out.
(This isnt really important in this case becaues we won't be reading any uninitiallised data from the array)
*/

bool Queue_enq(Queue* this, void* element) {
    int next;

    next = (this->head + 1);
    if (next >= this->max_size)
        next = 0;
    
    if (next == this->tail || element == NULL)
        return false;

    this->data[this->head] = element;
    this->head = next;
    this->size++;
    return true;
}

void* Queue_deq(Queue* this) {
    int next;
    void *elem;

    if (Queue_isEmpty(this)) // return null if queue is empty
        return NULL;

    next = (this->tail + 1); // where next element would be
    if (next >= this->max_size) // wrap to start of queue to make it circular
        next = 0;

    elem = this->data[this->tail];
    this->tail = next;
    this->size--;

    return elem;
}

int Queue_size(Queue* this) {
    return this->size;
}

bool Queue_isEmpty(Queue* this) {
    return (this->tail == this->head);
}

void Queue_clear(Queue* this) {
    if(this) {
        this->head = 0;
        this->tail = 0;
        this->size = 0;
        
        if (Queue_isEmpty(this) == false) {
            for (int i = 0; i < this->max_size; i++) {
                this->data[i] = NULL;
            }
        }
    }
}

void Queue_destroy(Queue* this) {
    if(this) {
        free(this->data);
        free(this);
    }
}
