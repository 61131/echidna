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
_test_priority_compare(const void *A, const void *B) {
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


static int 
_test_priority_destroy(const MunitParameter Parameters[], void *Fixture) {
    munit_assert_not_null(NULL);
    return MUNIT_FAIL;
}


MunitResult
test_priority_equal(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;
    struct _QUEUE_ELEMENT sItem[] = {
        { 2, "Two" },
        { 1, "One" },
        { 2, "Three" },
        { 2, "Four" },

        { -1, NULL }
    };
    struct _QUEUE_ELEMENT *pItem;
    int nCount, nIndex, nResult;

    queue_initialise(&sQueue, _test_priority_compare, _test_priority_destroy);
    munit_assert_size(queue_size(&sQueue, 6), ==, 6);
    munit_assert_size(sQueue.Count, ==, 0);
    for(nIndex = 0; sItem[nIndex].Data != NULL; ++nIndex) {
        munit_assert_int(queue_push(&sQueue, &sItem[nIndex]), ==, 0);
        munit_assert_size(sQueue.Count, ==, (nIndex + 1));
    }
    nCount = nIndex;
    nIndex = 0;
    while(sQueue.Count != 0) {
        munit_assert_not_null(pItem = queue_pop(&sQueue));
        switch(nIndex++) {
            case 0: nResult = strcmp(pItem->Data, "One"); break;
            case 1: nResult = strcmp(pItem->Data, "Two"); break;
            case 2: nResult = strcmp(pItem->Data, "Three"); break;
            case 3: nResult = strcmp(pItem->Data, "Four"); break;
            default:
                nResult = -1;
                break;
        }
        munit_assert_int(nResult, ==, 0);
    }
    munit_assert_int(nIndex, ==, nCount);
    queue_destroy(&sQueue, NULL);

    return MUNIT_OK;
}


MunitResult
test_priority_ordered(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;
    struct _QUEUE_ELEMENT sItem[] = {
        { 6, "Pear" },
        { 2, "Banana" },
        { 3, "Grape" },
        { 1, "Apple" },
        { 4, "Lemon" },
        { 5, "Orange" },

        { -1, NULL }
    };
    struct _QUEUE_ELEMENT *pItem;
    int nCount, nIndex, nResult;

    queue_initialise(&sQueue, _test_priority_compare, _test_priority_destroy);
    munit_assert_size(queue_size(&sQueue, 6), ==, 6);
    munit_assert_size(sQueue.Count, ==, 0);
    for(nIndex = 0; sItem[nIndex].Data != NULL; ++nIndex) {
        munit_assert_int(queue_push(&sQueue, &sItem[nIndex]), ==, 0);
        munit_assert_size(sQueue.Count, ==, (nIndex + 1));
    }
    nCount = nIndex;
    nIndex = 0;
    while(sQueue.Count != 0) {
        munit_assert_not_null(pItem = queue_pop(&sQueue));
        switch(nIndex++) {
            case 0: nResult = strcmp(pItem->Data, "Apple"); break;
            case 1: nResult = strcmp(pItem->Data, "Banana"); break;
            case 2: nResult = strcmp(pItem->Data, "Grape"); break;
            case 3: nResult = strcmp(pItem->Data, "Lemon"); break;
            case 4: nResult = strcmp(pItem->Data, "Orange"); break;
            case 5: nResult = strcmp(pItem->Data, "Pear"); break;
            default:
                nResult = -1;
                break;
        }
        munit_assert_int(nResult, ==, 0);
    }
    munit_assert_int(nIndex, ==, nCount);
    queue_destroy(&sQueue, NULL);

    return MUNIT_OK;
}


MunitResult
test_priority_negative(const MunitParameter Parameters[], void *Fixture) {
    QUEUE sQueue;
    struct _QUEUE_ELEMENT sItem[] = {
        { 6, "Pear" },
        { 2, "Banana" },
        { 3, "Grape" },
        { -1, "Apple" },
        { 4, "Lemon" },
        { 5, "Orange" },

        { -1, NULL }
    };
    struct _QUEUE_ELEMENT *pItem;
    int nCount, nIndex, nResult;

    queue_initialise(&sQueue, _test_priority_compare, _test_priority_destroy);
    munit_assert_size(queue_size(&sQueue, 6), ==, 6);
    munit_assert_size(sQueue.Count, ==, 0);
    for(nIndex = 0; sItem[nIndex].Data != NULL; ++nIndex) {
        munit_assert_int(queue_push(&sQueue, &sItem[nIndex]), ==, 0);
        munit_assert_size(sQueue.Count, ==, (nIndex + 1));
    }
    nCount = nIndex;
    nIndex = 0;
    while(sQueue.Count != 0) {
        munit_assert_not_null(pItem = queue_pop(&sQueue));
        switch(nIndex++) {
            case 0: nResult = strcmp(pItem->Data, "Banana"); break;
            case 1: nResult = strcmp(pItem->Data, "Grape"); break;
            case 2: nResult = strcmp(pItem->Data, "Lemon"); break;
            case 3: nResult = strcmp(pItem->Data, "Orange"); break;
            case 4: nResult = strcmp(pItem->Data, "Pear"); break;
            case 5: nResult = strcmp(pItem->Data, "Apple"); break;
            default:
                nResult = -1;
                break;
        }
        munit_assert_int(nResult, ==, 0);
    }
    munit_assert_int(nIndex, ==, nCount);
    queue_destroy(&sQueue, NULL);

    return MUNIT_OK;
}


