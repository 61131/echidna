#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <queue.h>


struct _QUEUE_ELEMENT {

    int Priority;
    char * Data;
};

static int
_test_queue_compare(const void *A, const void *B) {
    struct _QUEUE_ELEMENT *pA, *pB;

    munit_assert_not_null(A);
    pA = *(struct _QUEUE_ELEMENT **) A;
    munit_assert_not_null(pA);
    munit_assert_not_null(B);
    pB = *(struct _QUEUE_ELEMENT **) B;
    munit_assert_not_null(pB);

    if(pA->Priority == pB->Priority)
        return 0;
    if(pA->Priority < 0)
        return 1;
    if(pB->Priority < 0)
        return 0;
    return (pA->Priority > pB->Priority);
}


MunitResult
test_queue_initialise(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;

    queue_initialise(&sQueue);
    munit_assert_null(sQueue.Queue);
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_size(sQueue.Size, ==, 0);
    munit_assert_uint8(sQueue.Alloc, ==, 0);
    queue_destroy(&sQueue);

    return MUNIT_OK;
}


MunitResult
test_queue_new(const MunitParameter Parameters[], void *Fixture) {
    QUEUE *pQueue;

    pQueue = queue_new();
    munit_assert_null(pQueue->Queue);
    munit_assert_size(pQueue->Count, ==, 0);
    munit_assert_size(pQueue->Size, ==, 0);
    munit_assert_uint8(pQueue->Alloc, !=, 0);
    queue_destroy(pQueue);

    return MUNIT_OK;
}


MunitResult
test_queue_operations(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;
    struct _QUEUE_ELEMENT sItem[] = {
        { 0, "Apple" },
        { 0, "Banana" },
    };
    struct _QUEUE_ELEMENT *pItem;
    int nIndex;

    queue_initialise(&sQueue, _test_queue_compare, NULL);
    munit_assert_size(queue_size(&sQueue, 2), ==, 2);
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_null(queue_peek(&sQueue));
    for(nIndex = 0; nIndex < 2; ++nIndex) {
        munit_assert_int(queue_push(&sQueue, &sItem[nIndex]), ==, 0);
        munit_assert_size(sQueue.Count, ==, (nIndex + 1));
    }
    munit_assert_size(sQueue.Count, ==, sQueue.Size);
    munit_assert_int(queue_push(&sQueue, &sItem[0]), ==, -1);
    munit_assert_int(errno, ==, ENOMEM);

    pItem = queue_peek(&sQueue);
    munit_assert_not_null(pItem);
    munit_assert_int(pItem->Priority, ==, 0);
    munit_assert_string_equal(pItem->Data, "Apple");
    munit_assert_size(queue_size(&sQueue), ==, 2);

    pItem = queue_pop(&sQueue);
    munit_assert_not_null(pItem);
    munit_assert_int(pItem->Priority, ==, 0);
    munit_assert_string_equal(pItem->Data, "Apple");
    munit_assert_size(sQueue.Count, ==, 1);
    pItem = queue_pop(&sQueue);
    munit_assert_not_null(pItem);
    munit_assert_int(pItem->Priority, ==, 0);
    munit_assert_string_equal(pItem->Data, "Banana");
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_size(queue_size(&sQueue), ==, 2);

    queue_destroy(&sQueue);

    return MUNIT_OK;
}


MunitResult
test_queue_size(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;

    queue_initialise(&sQueue);
    munit_assert_null(sQueue.Queue);
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_size(sQueue.Size, ==, 0);
    munit_assert_size(sQueue.Size, ==, queue_size(&sQueue));
    munit_assert_size(queue_size(&sQueue, 5), ==, 5);
    munit_assert_size(queue_size(&sQueue), ==, 5);
    munit_assert_not_null(sQueue.Queue);
    munit_assert_size(sQueue.Count, ==, 0);
    queue_destroy(&sQueue);

    return MUNIT_OK;
}


