#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <tree.h>


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
test_tree_new(const MunitParameter Parameters[], void *Fixture) {
    TREE *pTree;

    pTree = tree_new();
    munit_assert_not_null(pTree);
    munit_assert_null(pTree->Root);
    munit_assert_size(pTree->Size, ==, 0);
    munit_assert_uint8(pTree->Alloc, !=, 0);
    tree_destroy(pTree);

    return MUNIT_OK;
}
