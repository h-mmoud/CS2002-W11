/*
 * TestQueue.c
 *
 * Very simple unit test file for Queue functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "myassert.h"
#include "Queue.h"


#define DEFAULT_MAX_QUEUE_SIZE 20

/*
 * The queue to use during tests
 */
static Queue *queue;

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
    queue = new_Queue(DEFAULT_MAX_QUEUE_SIZE);
    total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
    Queue_destroy(queue);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
    setup();

    if (testFunction()) success_count++;

    teardown();
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
 * Checks that the Queue constructor returns a non-NULL pointer.
 */
int newQueueIsNotNull() {
    assert(queue != NULL);
    return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty queue is 0.
 */
int newQueueSizeZero() {
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}


/*
 * Write more of your own test functions below (such as enqOneElement, enqAndDeqOneElement, ...)
 * to help you verify correctness of your Queue
 */


/*
    **************** Regular test cases ****************
*/

// Checks that enqueuing one element to the queue works correctly.
int enqOneElement() {
    int element = 5;
    assert(Queue_enq(queue, &element));
    return TEST_SUCCESS;
}



// Checks that enqueuing and dequeuing one element from the queue works correctly.
int enqAndDeqOneElement() {
    int element = 5;

    assert(Queue_enq(queue, &element));
    assert(Queue_deq(queue) == &element);

    return TEST_SUCCESS;
}


// Checks that enqueuing and dequeuing two elements from the queue works correctly.
int enqAndDeqTwoElements() {
    int element1 = 5;
    int element2 = 10;

    assert(Queue_enq(queue, &element1));
    assert(Queue_enq(queue, &element2));
    assert(Queue_deq(queue) == &element1);
    assert(Queue_deq(queue) == &element2);

    return TEST_SUCCESS;
}

// Checks that the size of the queue is correct after enqueuing and dequeuing elements.
int sizeOfQueue() {
    int element = 5;
    int element2 = 10;

    assert(Queue_enq(queue, &element));
    assert(Queue_enq(queue, &element2));
    assert(Queue_size(queue) == 2);
    assert(Queue_deq(queue) == &element);
    assert(Queue_size(queue) == 1);
    assert(Queue_deq(queue) == &element2);

    return TEST_SUCCESS;
}

// Checks the size of the queue is correct after it wraps around
int sizeAfterWrapping() {
    int element = 5;
    for (int i = 0; i < 11; i++) {
        assert(Queue_enq(queue, &element));
    }
    for (int i = 0; i < 11; i++) {
        assert(Queue_deq(queue) == &element);
    }
    for (int i = 0; i < 11; i++) {
        assert(Queue_enq(queue, &element));
    }

    assert(Queue_size(queue) == 11);
    return TEST_SUCCESS;
}

// Checks that the queue when initialised
int queueIsEmpty() {
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks that the queue is not empty after enqueuing an element
int queueIsNotEmpty() {
    int element = 5;
    assert(Queue_enq(queue, &element));
    assert(!Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks that the queue is empty after dequeuing an element
int queueIsEmptyAfterDeq() {
    int element = 5;
    assert(Queue_enq(queue, &element));
    assert(Queue_deq(queue) == &element);
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks clear function works correctly
int clearQueue() {
    int element = 5;
    for (int i = 0; i < 5; i++) {
        assert(Queue_enq(queue, &element));
    }
    Queue_clear(queue);
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks dequeueing after clearing returns NULL
int deqAfterClear() {
    int element = 5;
    for (int i = 0; i < 5; i++) {
        assert(Queue_enq(queue, &element));
    }
    Queue_clear(queue);
    assert(Queue_deq(queue) == NULL);
    return TEST_SUCCESS;
}

// Checks enqueuing after clearing works correctly
int enqAfterClear() {
    int element = 5;
    for (int i = 0; i < 5; i++) {
        assert(Queue_enq(queue, &element));
    }
    Queue_clear(queue);
    assert(Queue_enq(queue, &element));
    return TEST_SUCCESS;
}

// Checks enqueuing and dequeuing after clearing works correctly
int enqDeqAfterClear() {
    int element = 5;
    for (int i = 0; i < 5; i++) {
        assert(Queue_enq(queue, &element));
    }
    Queue_clear(queue);
    assert(Queue_enq(queue, &element));
    assert(Queue_deq(queue) == &element);
    return TEST_SUCCESS;
}

/*
    **************** Data type test cases ****************
*/

// Checks that the queue can store integers correctly
int queueStoresInts() {
    int intVal = 5;
    assert(Queue_enq(queue, &intVal));
    assert(*(int *)(Queue_deq(queue)) == intVal);
    return TEST_SUCCESS;
}

// Checks that the queue can store floats correctly
int queueStoresFloats() {
    float floatVal = 123.456f;
    Queue_enq(queue, &floatVal);
    assert(fabs(*(float*)Queue_deq(queue) - floatVal) < 0.001); // difference is checked to be less than 0.001 to account for potential precision errors in floating-point arithmetic.
    return TEST_SUCCESS;
}

int queueStoresChars() {
    char charVal = 'a';
    Queue_enq(queue, &charVal);
    assert(*(char*)Queue_deq(queue) == charVal);
    return TEST_SUCCESS;
}

int queueStoresStrings() {
    char *stringVal = "Hello, World!";
    Queue_enq(queue, stringVal);
    assert((char*)Queue_deq(queue) == stringVal);
    return TEST_SUCCESS;
}

int queueStoresPointers() {
    int intVal = 5;
    int *intPtr = &intVal;
    Queue_enq(queue, &intPtr);
    assert(*(int**)Queue_deq(queue) == intPtr);
    return TEST_SUCCESS;
}

int queueStoresUnions() {
    typedef union {
        int i;
    } MyUnion;

    MyUnion u;
    u.i = 10;

    Queue_enq(queue, &u);

    MyUnion *p = (MyUnion*)Queue_deq(queue);
    assert(p->i == u.i);

    return TEST_SUCCESS;
}

int queueStoresArrays() {
    int arr[3] = {1, 2, 3};

    Queue_enq(queue, arr);

    int *dequeuedArr = (int*)Queue_deq(queue);
    assert(dequeuedArr[0] == arr[0]);
    assert(dequeuedArr[1] == arr[1]);
    assert(dequeuedArr[2] == arr[2]);

    return TEST_SUCCESS;
}

int queueStoresStructs() {
    typedef struct {
        int x;
        int y;
    } Struc;

    Struc struc = {5, 10};
    Queue_enq(queue, &struc);

    Struc *s = (Struc*)Queue_deq(queue);
    assert(s->x == struc.x);
    assert(s->y == struc.y);
    return TEST_SUCCESS;
}

int queueStoresMixedTypes() {
    int intVal = 5;
    float floatVal = 123.456f;
    char charVal = 'a';
    char *stringVal = "Hello, World!";
    int *intPtr = &intVal;
    int arr[3] = {1, 2, 3};
    
    typedef union {
        int i;
    } MyUnion;
    MyUnion u;
    u.i = 10;

    typedef struct {
        int x;
        int y;
    } Struc;
    Struc struc = {5, 10};



    Queue_enq(queue, &intVal);
    Queue_enq(queue, &floatVal);
    Queue_enq(queue, &charVal);
    Queue_enq(queue, stringVal);
    Queue_enq(queue, &intPtr);
    Queue_enq(queue, &arr);
    Queue_enq(queue, &u);
    Queue_enq(queue, &struc);

    assert(*(int*)Queue_deq(queue) == intVal);
    assert(fabs(*(float*)Queue_deq(queue) - floatVal) < 0.001);
    assert(*(char*)Queue_deq(queue) == charVal);
    assert((char*)Queue_deq(queue) == stringVal);
    assert(*(int**)Queue_deq(queue) == intPtr);
    assert((int*)Queue_deq(queue) == arr);

    MyUnion *p = (MyUnion*)Queue_deq(queue);
    assert(p->i == u.i);

    Struc *s = (Struc*)Queue_deq(queue);
    assert(s->x == struc.x);
    assert(s->y == struc.y);

    return TEST_SUCCESS;
}


/*
    **************** Edge test cases ****************
*/


// Checks that the queue can be filled to its maximum capacity.
int enqMaxElements() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    return TEST_SUCCESS;
}

// Checks that the queue can be emptied of all elements.
int deqMaxElements() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_deq(queue) == &element);
    }
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}


// Checks that the queue can be enqueued once and dequeued twice.
int enqOnceDeqTwice() {
    int element = 5;
    assert(Queue_enq(queue, &element));
    assert(Queue_deq(queue) == &element);
    assert(Queue_deq(queue) == NULL);
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}

// Checks that the circular queue wraps around when enqueuing more elements than its maximum capacity.
int enqWrapsAround() {
    int element = 5;
    for (int i = 0; i < (DEFAULT_MAX_QUEUE_SIZE/2); i++) {
        assert(Queue_enq(queue, &element));
    }
    for (int i = 0; i < (DEFAULT_MAX_QUEUE_SIZE/2); i++) {
        assert(Queue_deq(queue) == &element);
    }
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }

    assert(Queue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);
    assert(Queue_deq(queue) == &element);
    return TEST_SUCCESS;
}

// Checks that the size of the queue is correct after enqueuing and dequeuing elements.
int sizeAfterEnqDeq() {
    int element = 5;
    assert(Queue_enq(queue, &element));
    assert(Queue_deq(queue) == &element);
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}

// Checks that the size of a full queue is equal to its maximum capacity.
int sizeFullQueue() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    assert(Queue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);
    return TEST_SUCCESS;
}

// Checks that the size of an empty queue is 0.
int sizeEmptyQueue() {
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}

// Checks that isEmpty works on an empty queue
int isEmptyEmptyQueue() {
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks that isEmpty works on a full queue
int isEmptyFullQueue() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    assert(!Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

int isEmptyFullDequeue() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }

    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_deq(queue) == &element);
    }
    
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks that clearing a full queue works correctly
int clearFullQueue() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    Queue_clear(queue);
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks clearing an empty queue works correctly
int clearEmptyQueue() {
    Queue_clear(queue);
    assert(Queue_isEmpty(queue));
    return TEST_SUCCESS;
}

// Checks that the queue is FIFO
int enqMaxDequeueAll() {
    int arr[DEFAULT_MAX_QUEUE_SIZE];
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        arr[i] = i;
        assert(Queue_enq(queue, &arr[i]));
    }

    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++){
        assert(Queue_deq(queue) == &arr[i]);
    }

    return TEST_SUCCESS;
}

// 
/*
    **************** Exceptional test cases ****************
*/


// Checks that the queue does not allow NULL elements to be enqueued.
int enqNullElement() {
    assert(!Queue_enq(queue, NULL));
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}


// Checks that the queue returns NULL when dequeuing an empty queue.
int deqEmptyQueue() {
    assert(Queue_deq(queue) == NULL);
    return TEST_SUCCESS;
}


// Checks that the queue does not allow more elements to be enqueued than its maximum capacity.
int enqOverMax() {
    int element = 5;
    for (int i = 0; i < DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(Queue_enq(queue, &element));
    }
    assert(!Queue_enq(queue, &element));
    assert(Queue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);
    return TEST_SUCCESS;
}




/*
 * Main function for the Queue tests which will run each user-defined test in turn.
 */

int main() {
    //regular cases
    runTest(newQueueIsNotNull);
    runTest(newQueueSizeZero);
    runTest(enqOneElement);
    runTest(enqAndDeqOneElement);
    runTest(enqAndDeqTwoElements);
    runTest(sizeOfQueue);
    runTest(sizeAfterWrapping);
    runTest(queueIsEmpty);
    runTest(queueIsNotEmpty);
    runTest(queueIsEmptyAfterDeq);
    runTest(clearQueue);
    runTest(deqAfterClear);
    runTest(enqAfterClear);
    runTest(enqDeqAfterClear);
    //data type cases
    runTest(queueStoresInts);
    runTest(queueStoresFloats);
    runTest(queueStoresChars);
    runTest(queueStoresStrings);
    runTest(queueStoresPointers);
    runTest(queueStoresArrays);
    runTest(queueStoresUnions);
    runTest(queueStoresStructs);
    runTest(queueStoresMixedTypes);
    //edge cases
    runTest(enqMaxElements);
    runTest(deqMaxElements);
    runTest(isEmptyEmptyQueue);
    runTest(isEmptyFullQueue);
    runTest(isEmptyFullDequeue);
    runTest(enqOnceDeqTwice);
    runTest(enqWrapsAround);
    runTest(sizeAfterEnqDeq);
    runTest(sizeFullQueue);
    runTest(sizeEmptyQueue);
    runTest(clearFullQueue);
    runTest(clearEmptyQueue);
    runTest(enqMaxDequeueAll);
    //exceptional cases
    runTest(enqNullElement);
    runTest(deqEmptyQueue);
    runTest(enqOverMax);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(enqOneElement);
     * runTest(enqAndDeqOneElement);
     *
     */

    printf("Queue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
