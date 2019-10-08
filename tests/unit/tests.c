#include <stdio.h>
#include <string.h>

#include <munit/munit.h>

#include <unit.h>


MunitResult
test_unit_create(const MunitParameter Parameters[], void *Fixture) {
    BLOCK *pBlock;
    UNIT *pUnit;

    pUnit = unit_create("_config", "_resource", "_pou");
    munit_assert_not_null(pUnit);
    munit_assert_not_null(pUnit->Config);
    munit_assert_string_equal(pUnit->Config, "_config");
    munit_assert_not_null(pUnit->Resource);
    munit_assert_string_equal(pUnit->Resource, "_resource");
    munit_assert_not_null(pUnit->POU);
    munit_assert_string_equal(pUnit->POU, "_pou");
    munit_assert_size(pUnit->Size, ==, 0);
    munit_assert_uint8(pUnit->Alloc, !=, 0);
    pBlock = &pUnit->Block;
    munit_assert_ptr(pBlock, ==, pUnit);
    munit_assert_not_null(block_name(pBlock));
    munit_assert_string_equal(block_name(pBlock), "_config._resource._pou");
    unit_destroy(pUnit);

    return MUNIT_OK;
}


MunitResult
test_unit_initialise(const MunitParameter Parameters[], void *Fixture) {
    UNIT sUnit;

    unit_initialise(&sUnit, NULL, NULL, NULL);
    munit_assert_null(sUnit.Config);
    munit_assert_null(sUnit.Resource);
    munit_assert_null(sUnit.POU);
    munit_assert_size(sUnit.Size, ==, 0);
    munit_assert_uint8(sUnit.Alloc, ==, 0);
    unit_destroy(&sUnit);

    unit_destroy(NULL);

    return MUNIT_OK;
}


MunitResult
test_unit_new(const MunitParameter Parameters[], void *Fixture) {
    UNIT *pUnit;

    pUnit = unit_new();
    munit_assert_not_null(pUnit);
    munit_assert_null(pUnit->Config);
    munit_assert_null(pUnit->Resource);
    munit_assert_null(pUnit->POU);
    munit_assert_size(pUnit->Size, ==, 0);
    munit_assert_uint8(pUnit->Alloc, !=, 0);
    unit_destroy(pUnit);

    return MUNIT_OK;
}
