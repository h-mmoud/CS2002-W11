/*
 * TestBlockingQueue.c
 *
 * Very simple unit test file for BlockingQueue functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>

#include "BlockingQueue.h"
#include "myassert.h"


#define DEFAULT_MAX_QUEUE_SIZE 20

/*
 * The queue to use during tests
 */
static BlockingQueue *queue;

/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test
 */
void setup(){
    queue = new_BlockingQueue(DEFAULT_MAX_QUEUE_SIZE);
    total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
    BlockingQueue_destroy(queue);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
    setup();

    if (testFunction()) success_count++;

    teardown();
}

void* threadFunc(void* arg) {
    int element = *(int*)arg;
    BlockingQueue_enq(queue, &element);
    BlockingQueue_deq(queue);
    return NULL;
}


/*
 * Two sample user-defined tests included below.
 * You will have to write many more tests.
 *
 * Each test function should return TEST_SUCCESS at the end.
 * Test functions can contain more than one assertion.
 *
 * If any assertion fails, the function name and line number
 * will be printed and the test will return a failure value.
 *
 * You will have to call runTest on your test functions in main below.
 */


/*
 * Checks that the BlockingQueue constructor returns a non-NULL pointer.
 */
int newQueueIsNotNull() {
    assert(queue != NULL);
    return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty blocking queue is 0.
 */
int newQueueSizeZero() {
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Write more of your own test functions below (such as enqOneElement, enqAndDeqOneElement, ...)
 * to help you verify correctness of your BlockingQueue.
 */

int enqAndDeqOneElement() {
    int element = 5;

    assert(BlockingQueue_enq(queue, &element));
    assert(*(int*)BlockingQueue_deq(queue) == element);

    return TEST_SUCCESS;
}

int enqAndDeqMultipleElements() {
    int elements[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        assert(BlockingQueue_enq(queue, &elements[i]));
    }
    for (int i = 0; i < 5; i++) {
        assert(*(int*)BlockingQueue_deq(queue) == elements[i]);
    }
    return TEST_SUCCESS;
}

int threadSafetyTest() {
    pthread_t threads[10];
    int elements[10];
    for (int i = 0; i < 10; i++) {
        elements[i] = i;
        pthread_create(&threads[i], NULL, threadFunc, &elements[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Main function for the BlockingQueue tests which will run each user-defined test in turn.
 */

int main() {
    runTest(newQueueIsNotNull);
    runTest(newQueueSizeZero);
    
    runTest(enqAndDeqOneElement);
    runTest(enqAndDeqMultipleElements);
    runTest(threadSafetyTest);

    printf("\nBlockingQueue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
