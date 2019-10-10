#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <tree.h>


static char * _Str[] = {
    "Apple",
    "Banana",
    "Orange",
    "Lemon",
    "Pear",
    "Strawberry",
    NULL
};


static int 
_test_tree_compare(void *A, void *B) {
    munit_assert_not_null(A);
    munit_assert_not_null(B);
    return strcmp((char *) A, (char *) B);
}


static void
_test_tree_populate(TREE *Tree) {
    int nIndex;

    tree_initialise(Tree);
    munit_assert_size(Tree->Size, ==, 0);
    for(nIndex = 0; _Str[nIndex] != NULL; ++nIndex) {
        munit_assert_int(tree_insert(Tree, _Str[nIndex]), ==, 0);
        munit_assert_size(Tree->Size, ==, (size_t) (nIndex + 1));
    }
}


MunitResult
test_tree_initialise(const MunitParameter Parameters[], void *Fixture) {
    TREE sTree;

    tree_initialise(&sTree, NULL, NULL);
    munit_assert_null(sTree.Root);
    munit_assert_size(sTree.Size, ==, 0);
    munit_assert_uint8(sTree.Alloc, ==, 0);
    tree_destroy(&sTree, NULL);

    tree_initialise(NULL);
    tree_destroy(NULL);

    return MUNIT_OK;
}


MunitResult
test_tree_iterate(const MunitParameter Parameters[], void *Fixture) {
    TREE sTree;
    TREE_ITER *pIter;
    char *pStr;
    int nIndex;

    _test_tree_populate(&sTree);
    pIter = tree_iterate_new(&sTree);
    munit_assert_not_null(pIter);

    //  Forward iteration

    nIndex = 0;
    tree_iterate_reset(pIter, &sTree);
    while((pStr = tree_iterate(pIter)) != NULL) {
        munit_assert_not_null(_Str[nIndex]);
        munit_assert_string_equal(_Str[nIndex++], pStr);
    }
    munit_assert_null(_Str[nIndex]);

    //  Forward iteration

    nIndex = 0;
    for(pStr = tree_iterate_first(pIter, &sTree);
            (_Str[nIndex] != NULL) && (pStr != NULL);
            pStr = tree_iterate_next(pIter)) {
        munit_assert_not_null(_Str[nIndex]);
        munit_assert_string_equal(_Str[nIndex++], pStr);
    }
    munit_assert_null(_Str[nIndex]);

    //  Reverse iteration

    --nIndex;
    for(pStr = tree_iterate_last(pIter, &sTree);
            (nIndex >= 0) &&
                    (_Str[nIndex] != NULL) && 
                    (pStr != NULL);
            pStr = tree_iterate_previous(pIter)) {
        munit_assert_not_null(_Str[nIndex]);
        munit_assert_string_equal(_Str[nIndex--], pStr);
    }
    munit_assert_int(nIndex, ==, -1);

    free(pIter);    //  TODO: Replace with tree_iterate_destroy?!
    tree_destroy(&sTree);

    return MUNIT_OK;
}


MunitResult
test_tree_operations(const MunitParameter Parameters[], void *Fixture) {
    TREE sTree;
    char *pStr;
    int nIndex;

    tree_initialise(&sTree, _test_tree_compare);
    munit_assert_size(sTree.Size, ==, 0);
    for(nIndex = 1; _Str[nIndex] != NULL; ++nIndex) {
        pStr = strdup(_Str[nIndex]);
        munit_assert_not_null(pStr);
        munit_assert_int(tree_insert(&sTree, pStr), ==, 0);
        munit_assert_size(sTree.Size, ==, (size_t) nIndex);
    }
    pStr = strdup(_Str[0]);
    munit_assert_not_null(pStr);
    munit_assert_int(tree_insert(&sTree, pStr), ==, 0);
    munit_assert_size(sTree.Size, ==, (size_t) nIndex);
    errno = 0;
    munit_assert_int(tree_insert(&sTree, pStr), ==, -1);
    munit_assert_int(errno, ==, EEXIST);

    for(nIndex = 0; _Str[nIndex] != NULL; ++nIndex)
        munit_assert_not_null(tree_search(&sTree, _Str[nIndex]));
    munit_assert_null(tree_search(&sTree, "Avocado"));

    tree_destroy(&sTree, free);

    return MUNIT_OK;
}


MunitResult
test_tree_new(const MunitParameter Parameters[], void *Fixture) {
    TREE *pTree;

    pTree = tree_new();
    munit_assert_not_null(pTree);
    munit_assert_null(pTree->Root);
    munit_assert_size(pTree->Size, ==, 0);
    munit_assert_uint8(pTree->Alloc, !=, 0);
    tree_destroy(pTree);

    tree_initialise(NULL);
    tree_destroy(NULL);

    return MUNIT_OK;
}


MunitResult
test_tree_remove(const MunitParameter Parameters[], void *Fixture) {
    TREE sTree;
    size_t uSize;

    _test_tree_populate(&sTree);
    uSize = sTree.Size;
    munit_assert_size(uSize, >, 0);
    munit_assert_int(tree_remove(&sTree, "Apple"), ==, 0);
    munit_assert_size(sTree.Size, ==, --uSize);
    errno = 0;
    munit_assert_int(tree_remove(&sTree, "Apple"), ==, -1);
    munit_assert_int(errno, ==, ENOENT);
    munit_assert_size(uSize, >, 0);
    munit_assert_int(tree_remove(&sTree, "Pear"), ==, 0);
    munit_assert_size(sTree.Size, ==, --uSize);
    tree_destroy(&sTree);

    return MUNIT_OK;
}


