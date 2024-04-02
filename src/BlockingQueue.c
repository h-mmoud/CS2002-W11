/*
 * BlockingQueue.c
 *
 * Fixed-size generic array-based BlockingQueue implementation.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include "BlockingQueue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the BlockingQueue module interface as documented in BlockingQueue.h.
 */


BlockingQueue *new_BlockingQueue(int max_size) {
    BlockingQueue *bQueue = malloc(sizeof(BlockingQueue));
    bQueue->queue = new_Queue(max_size);
    
    pthread_mutex_init(&bQueue->mutex, NULL);
    sem_init(&bQueue->available, 0, max_size);
    sem_init(&bQueue->current_size, 0, 0);
    return bQueue;
}

bool BlockingQueue_enq(BlockingQueue* this, void* element) {
    sem_wait(&(this->available)); // Wait for space in the queue

    pthread_mutex_lock(&(this->mutex)); 
    bool result = Queue_enq(this->queue, element);
    pthread_mutex_unlock(&(this->mutex));

    if (result) sem_post(&(this->current_size)); // Signal that there is an element in the queue

    return result;
}

void* BlockingQueue_deq(BlockingQueue* this) {
    sem_wait(&(this->current_size)); // Wait for an element in the queue, current size above 0
    pthread_mutex_lock(&(this->mutex)); 

    void* element = Queue_deq(this->queue);

    pthread_mutex_unlock(&(this->mutex));
    sem_post(&(this->available)); // Signal that there is space in the queue

    return element;
}

int BlockingQueue_size(BlockingQueue* this) {
    int size;

    pthread_mutex_lock(&(this->mutex));
    size = Queue_size(this->queue);
    pthread_mutex_unlock(&(this->mutex));

    return size;
}

bool BlockingQueue_isEmpty(BlockingQueue* this) {
    bool isEmpty;

    pthread_mutex_lock(&(this->mutex));
    isEmpty = Queue_isEmpty(this->queue);
    pthread_mutex_unlock(&(this->mutex));

    return isEmpty;
}

void BlockingQueue_clear(BlockingQueue* this) {
    pthread_mutex_lock(&(this->mutex));
    Queue_clear(this->queue);
    pthread_mutex_unlock(&(this->mutex));
}

void BlockingQueue_destroy(BlockingQueue* this) {
    pthread_mutex_destroy(&(this->mutex));
    sem_destroy(&(this->available));
    sem_destroy(&(this->current_size));
    Queue_destroy(this->queue);
    free(this);
}

// int main() {
//     BlockingQueue *queue = new_BlockingQueue(10);

//     printf("Hello, World!\n");
//     int elem = 5;
//     BlockingQueue_enq(queue, &elem);

//     return 0;
// }