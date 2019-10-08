#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <queue.h>


struct _QUEUE_ELEMENT {

    int Priority;
    char * Data;
};


MunitResult
test_queue_initialise(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;

    queue_initialise(&sQueue);
    munit_assert_null(sQueue.Queue);
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_size(sQueue.Size, ==, 0);
    munit_assert_uint8(sQueue.Alloc, ==, 0);
    queue_destroy(&sQueue);

    queue_destroy(NULL);

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

    queue_initialise(&sQueue, NULL, NULL);
    //  queue_size: 0 -> 4
    munit_assert_size(queue_size(&sQueue, 4), ==, 4);
    //  queue_size: 4 -> 2
    munit_assert_size(queue_size(&sQueue, 2), ==, 2);

    munit_assert_int(queue_push(&sQueue, NULL), ==, 0);
    munit_assert_size(sQueue.Count, ==, 0);
    munit_assert_null(queue_peek(&sQueue));
    munit_assert_null(queue_pop(&sQueue));

    for(nIndex = 0; nIndex < 2; ++nIndex) {
        munit_assert_not_null(pItem = calloc(1, sizeof(struct _QUEUE_ELEMENT)));
        pItem->Priority = sItem[nIndex].Priority;
        pItem->Data = sItem[nIndex].Data;
        munit_assert_int(queue_push(&sQueue, pItem), ==, 0);
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
    free(pItem);

    queue_destroy(&sQueue, free);

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


