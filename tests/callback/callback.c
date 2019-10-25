#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <munit/munit.h>

#include <callback.h>
#include <echidna.h>


static void
_test_callback_callback(ECHIDNA *Context, void *Arg, void *User) {
}


MunitResult
test_callback_register(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    munit_assert_int(callback_register(pContext, CALLBACK_NONE), ==, -1);
    munit_assert_int(callback_register(pContext, CALLBACK_TASK_START), ==, -1);
    munit_assert_int(callback_register(pContext, CALLBACK_TASK_START, NULL), ==, -1);
    munit_assert_int(callback_register(pContext, CALLBACK_TASK_START, NULL, _test_callback_callback), ==, 0);
    munit_assert_int(callback_register(pContext, CALLBACK_TASK_STOP, NULL, _test_callback_callback), ==, 0);
    munit_assert_int(callback_register(pContext, CALLBACK_CYCLE_START, NULL, _test_callback_callback), ==, 0);
    munit_assert_int(callback_register(pContext, CALLBACK_CYCLE_FINISH, NULL, _test_callback_callback), ==, 0);

    return MUNIT_OK;
}
