#include <stdio.h>
#include <string.h>
#include <strings.h>

#include <munit/munit.h>

#include <ll.h>


static char * _Str[] = {
    "Apple",
    "Banana",
    "Orange",
    "Pear",
    "Watermelon",
    NULL,
};

static void
_test_ll_populate(LL *List, int Head) {
    int nIndex;

    munit_assert_int(ll_initialise(List, NULL), ==, 0);
    munit_assert_size(List->Size, ==, 0);
    for(nIndex = 0; _Str[nIndex]; nIndex++) {
        if(Head)
            munit_assert_int(ll_insert_head(List, _Str[nIndex]), ==, 0);
        else
            munit_assert_int(ll_insert_tail(List, _Str[nIndex]), ==, 0);
        munit_assert_size(List->Size, ==, (nIndex + 1));
    }
}


static void
_test_ll_validate(LL *List) {
    LL_ITER sIt;
    char *pStr;
    int nIndex;

    nIndex = 0;
    munit_assert_size(List->Size, ==, 5);
    for(pStr = ll_iterate_first(&sIt, List);
            pStr;
            pStr = ll_iterate_next(&sIt)) 
        munit_assert_string_equal(pStr, _Str[nIndex++]);
}


MunitResult
test_ll_copy(const MunitParameter Parameters[], void *Fixture) {
    LL sList1, sList2;

    _test_ll_populate(&sList1, 0);
    _test_ll_validate(&sList1);
    munit_assert_int(ll_initialise(&sList2, NULL), ==, 0);
    munit_assert_size(sList2.Size, ==, 0);
    munit_assert_int(ll_copy(&sList2, &sList1), ==, 0);
    munit_assert_size(sList1.Size, ==, sList2.Size);
    _test_ll_validate(&sList2);
    ll_destroy(&sList2);
    ll_destroy(&sList1);

    return MUNIT_OK;
}


MunitResult
test_ll_delete(const MunitParameter Parameters[], void *Fixture) {
    LL sList;
    LL_ITER sIt;
    LLE *pElement;
    char *pStr;
    int nIndex;

    _test_ll_populate(&sList, 0);

    pElement = sList.Head;
    ll_delete(pElement, (void **) &pStr);
    munit_assert_string_equal(pStr, "Apple");
    munit_assert_size(sList.Size, ==, 4);

    pElement = sList.Tail;
    ll_delete(pElement, (void **) &pStr);
    munit_assert_string_equal(pStr, "Watermelon");
    munit_assert_size(sList.Size, ==, 3);

    for(pElement = sList.Head; pElement; pElement = pElement->Next) {
        if(strcasecmp(pElement->Data, "Orange") == 0) {
            ll_delete(pElement);
            break;
        }
    }
    munit_assert_size(sList.Size, ==, 2);

    nIndex = 0;
    for(pStr = ll_iterate_first(&sIt, &sList);
            pStr != NULL;
            pStr = ll_iterate_next(&sIt)) {
        switch(nIndex++) {
            case 0: 
                munit_assert_string_equal(pStr, "Banana");
                break;

            case 1:
                munit_assert_string_equal(pStr, "Pear");
                break;

            default:
                return MUNIT_FAIL;
        }
    }

    ll_destroy(&sList);
    return MUNIT_OK;
}


MunitResult
test_ll_initialise(const MunitParameter Parameters[], void *Fixture) {
    LL sList;

    munit_assert_int(ll_initialise(&sList), ==, 0);
    munit_assert_size(sList.Size, ==, 0);
    munit_assert_null(sList.Head);
    munit_assert_null(sList.Tail);
    munit_assert_uint8(sList.Alloc, ==, 0);
    ll_destroy(&sList);

    return MUNIT_OK;
}


MunitResult
test_ll_insert_head(const MunitParameter Parameters[], void *Fixture) {
    LL sList;
    LL_ITER sIt;
    char *pStr;
    int nIndex;

    _test_ll_populate(&sList, 1);

    nIndex = 5;
    for(pStr = ll_iterate_first(&sIt, &sList);
            (nIndex < 0) || (pStr != NULL);
            pStr = ll_iterate_next(&sIt)) 
        munit_assert_string_equal(pStr, _Str[--nIndex]);
    munit_assert_int(nIndex, ==, 0);
    ll_destroy(&sList);

    return MUNIT_OK;
}


MunitResult
test_ll_insert_tail(const MunitParameter Parameters[], void *Fixture) {
    LL sList;

    _test_ll_populate(&sList, 0);
    _test_ll_validate(&sList);
    ll_destroy(&sList);

    return MUNIT_OK;
}


MunitResult
test_ll_iterate_first(const MunitParameter Parameters[], void *Fixture) {
    LL sList;
    LL_ITER sIt;
    char *pStr;

    ll_initialise(&sList);
    munit_assert_null(ll_iterate_first(&sIt, &sList));

    _test_ll_populate(&sList, 0);
    munit_assert_not_null(pStr = ll_iterate_first(&sIt, &sList));
    munit_assert_string_equal(pStr, "Apple");
    ll_destroy(&sList);

    return MUNIT_OK;
}


MunitResult
test_ll_iterate_last(const MunitParameter Parameters[], void *Fixture) {
    LL sList;
    LL_ITER sIt;
    char *pStr;

    ll_initialise(&sList);
    munit_assert_null(ll_iterate_last(&sIt, &sList));

    _test_ll_populate(&sList, 0);
    munit_assert_not_null(pStr = ll_iterate_last(&sIt, &sList));
    munit_assert_string_equal(pStr, "Watermelon");
    ll_destroy(&sList);

    return MUNIT_OK;
}


MunitResult
test_ll_merge(const MunitParameter Parameters[], void *Fixture) {
    LL sList1, sList2;
    size_t uSize;

    _test_ll_populate(&sList1, 0);
    munit_assert_int(ll_initialise(&sList2, NULL), ==, 0);
    munit_assert_size(sList2.Size, ==, 0);
    uSize = sList1.Size;
    munit_assert_int(ll_merge(&sList2, &sList1), ==, 0);
    munit_assert_size(sList1.Size, ==, 0);
    munit_assert_size(sList2.Size, ==, uSize);
    _test_ll_validate(&sList2);
    ll_destroy(&sList2);
    ll_destroy(&sList1);

    return MUNIT_OK;
}


MunitResult
test_ll_new(const MunitParameter Parameters[], void *Fixture) {
    LL *pList;

    pList = ll_new();
    munit_assert_not_null(pList);
    munit_assert_size(pList->Size, ==, 0);
    munit_assert_null(pList->Head);
    munit_assert_null(pList->Tail);
    munit_assert_uint8(pList->Alloc, !=, 0);
    ll_destroy(pList);

    return MUNIT_OK;
}


