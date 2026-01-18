/*
 * zztest - A test framework for crufty compilers.
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

#undef FAIL
#undef SKIP

#include "catch2/catch_all.hpp"

/******************************************************************************/

struct zzt_test_state_s {
    struct zzt_test_s *test;
    int passed;
    int failed;
    int skipped;
};

static zzt_test_state_s
RunTest(const zzt_test_s &test)
{
    zzt_test_state_s state = {0};
    test.func(&state);
    return state;
}

struct test_s {
    int passed = 0;
    int failed = 0;
    zzt_test_s *test = nullptr;
};

/******************************************************************************/

TEST(metatest, testtrue)
{
    EXPECT_TRUE(true == true);
    ASSERT_TRUE(true == true);
    EXPECT_TRUE(true == false);
    ASSERT_TRUE(true == false);
    EXPECT_TRUE(true == false);
}

TEST(metatest, testfalse)
{
    EXPECT_FALSE(true == false);
    ASSERT_FALSE(true == false);
    EXPECT_FALSE(true == true);
    ASSERT_FALSE(true == true);
    EXPECT_FALSE(true == true);
}

TEST_CASE("TRUE/FALSE")
{
    auto test = GENERATE(                                //
        test_s{2, 2, &ZZT_TESTINFO(metatest, testtrue)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, testtrue)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, booleq)
{
    EXPECT_BOOLEQ(true, true);
    ASSERT_BOOLEQ(true, true);
    EXPECT_BOOLEQ(true, false);
    ASSERT_BOOLEQ(true, false);
    EXPECT_BOOLEQ(true, false);
}

TEST(metatest, boolne)
{
    EXPECT_BOOLNE(true, false);
    ASSERT_BOOLNE(true, false);
    EXPECT_BOOLNE(true, true);
    ASSERT_BOOLNE(true, true);
    EXPECT_BOOLNE(true, true);
}

TEST(metatest, boolint)
{
    EXPECT_BOOLEQ(1, 2);
    ASSERT_BOOLEQ(1, 2);
    EXPECT_BOOLNE(1, 2);
    ASSERT_BOOLNE(1, 2);
    EXPECT_BOOLNE(1, 2);
}

TEST_CASE("ASSERT_BOOL")
{
    auto test = GENERATE(                              //
        test_s{2, 2, &ZZT_TESTINFO(metatest, booleq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, boolne)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, boolint)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, assert_chareq)
{
    EXPECT_CHAREQ('a', 'a');
    ASSERT_CHAREQ('a', 'a');
    EXPECT_CHAREQ('a', 'b');
    ASSERT_CHAREQ('a', 'b');
    EXPECT_CHAREQ('a', 'b');
}

TEST(metatest, assert_charne)
{
    EXPECT_CHARNE('a', 'b');
    ASSERT_CHARNE('a', 'b');
    EXPECT_CHARNE('a', 'a');
    ASSERT_CHARNE('a', 'a');
    EXPECT_CHARNE('a', 'a');
}

TEST(metatest, assert_charlt)
{
    EXPECT_CHARLT('a', 'b');
    ASSERT_CHARLT('a', 'b');
    EXPECT_CHARLT('a', 'a');
    ASSERT_CHARLT('a', 'a');
    EXPECT_CHARLT('a', 'a');
}

TEST(metatest, assert_charle)
{
    EXPECT_CHARLE('a', 'b');
    ASSERT_CHARLE('a', 'b');
    EXPECT_CHARLE('a', 'a');
    ASSERT_CHARLE('a', 'a');
    EXPECT_CHARLE('b', 'a');
    ASSERT_CHARLE('b', 'a');
    EXPECT_CHARLE('b', 'a');
}

TEST(metatest, assert_chargt)
{
    EXPECT_CHARGT('b', 'a');
    ASSERT_CHARGT('b', 'a');
    EXPECT_CHARGT('b', 'b');
    ASSERT_CHARGT('b', 'b');
    EXPECT_CHARGT('b', 'b');
}

TEST(metatest, assert_charge)
{
    EXPECT_CHARGE('b', 'a');
    ASSERT_CHARGE('b', 'a');
    EXPECT_CHARGE('a', 'a');
    ASSERT_CHARGE('a', 'a');
    EXPECT_CHARGE('a', 'b');
    ASSERT_CHARGE('a', 'b');
    EXPECT_CHARGE('a', 'b');
}

TEST_CASE("CHAR")
{
    auto test = GENERATE(                                     //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_chareq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_charne)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_charlt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_charle)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_chargt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_charge)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, assert_inteq)
{
    EXPECT_INTEQ(-1, -1);
    ASSERT_INTEQ(-1, -1);
    EXPECT_INTEQ(-1, 1);
    ASSERT_INTEQ(-1, 1);
    EXPECT_INTEQ(-1, 1);
}

TEST(metatest, assert_intne)
{
    EXPECT_INTNE(-1, 1);
    ASSERT_INTNE(-1, 1);
    EXPECT_INTNE(-1, -1);
    ASSERT_INTNE(-1, -1);
    EXPECT_INTNE(-1, -1);
}

TEST(metatest, assert_intlt)
{
    EXPECT_INTLT(-1, 1);
    ASSERT_INTLT(-1, 1);
    EXPECT_INTLT(-1, -1);
    ASSERT_INTLT(-1, -1);
    EXPECT_INTLT(-1, -1);
}

TEST(metatest, assert_intle)
{
    EXPECT_INTLE(-1, 1);
    ASSERT_INTLE(-1, 1);
    EXPECT_INTLE(-1, -1);
    ASSERT_INTLE(-1, -1);
    EXPECT_INTLE(1, -1);
    ASSERT_INTLE(1, -1);
    EXPECT_INTLE(1, -1);
}

TEST(metatest, assert_intgt)
{
    EXPECT_INTGT(1, -1);
    ASSERT_INTGT(1, -1);
    EXPECT_INTGT(1, 1);
    ASSERT_INTGT(1, 1);
    EXPECT_INTGT(1, 1);
}

TEST(metatest, assert_intge)
{
    EXPECT_INTGE(1, -1);
    ASSERT_INTGE(1, -1);
    EXPECT_INTGE(-1, -1);
    ASSERT_INTGE(-1, -1);
    EXPECT_INTGE(-1, 1);
    ASSERT_INTGE(-1, 1);
    EXPECT_INTGE(-1, 1);
}

TEST_CASE("INT")
{
    auto test = GENERATE(                                    //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_inteq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_intne)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_intlt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_intle)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_intgt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_intge)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, assert_uinteq)
{
    EXPECT_UINTEQ(0, 0);
    ASSERT_UINTEQ(0, 0);
    EXPECT_UINTEQ(0, 1);
    ASSERT_UINTEQ(0, 1);
    EXPECT_UINTEQ(0, 1);
}

TEST(metatest, assert_uintne)
{
    EXPECT_UINTNE(0, 1);
    ASSERT_UINTNE(0, 1);
    EXPECT_UINTNE(0, 0);
    ASSERT_UINTNE(0, 0);
    EXPECT_UINTNE(0, 0);
}

TEST(metatest, assert_uintlt)
{
    EXPECT_UINTLT(0, 1);
    ASSERT_UINTLT(0, 1);
    EXPECT_UINTLT(0, 0);
    ASSERT_UINTLT(0, 0);
    EXPECT_UINTLT(0, 0);
}

TEST(metatest, assert_uintle)
{
    EXPECT_UINTLE(0, 1);
    ASSERT_UINTLE(0, 1);
    EXPECT_UINTLE(0, 0);
    ASSERT_UINTLE(0, 0);
    EXPECT_UINTLE(1, 0);
    ASSERT_UINTLE(1, 0);
    EXPECT_UINTLE(1, 0);
}

TEST(metatest, assert_uintgt)
{
    EXPECT_UINTGT(1, 0);
    ASSERT_UINTGT(1, 0);
    EXPECT_UINTGT(1, 1);
    ASSERT_UINTGT(1, 1);
    EXPECT_UINTGT(1, 1);
}

TEST(metatest, assert_uintge)
{
    EXPECT_UINTGE(1, 0);
    ASSERT_UINTGE(1, 0);
    EXPECT_UINTGE(0, 0);
    ASSERT_UINTGE(0, 0);
    EXPECT_UINTGE(0, 1);
    ASSERT_UINTGE(0, 1);
    EXPECT_UINTGE(0, 1);
}

TEST_CASE("UINT")
{
    auto test = GENERATE(                                     //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_uinteq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_uintne)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_uintlt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_uintle)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_uintgt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_uintge)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, assert_xinteq)
{
    EXPECT_XINTEQ(0, 0);
    ASSERT_XINTEQ(0, 0);
    EXPECT_XINTEQ(0, 1);
    ASSERT_XINTEQ(0, 1);
    EXPECT_XINTEQ(0, 1);
}

TEST(metatest, assert_xintne)
{
    EXPECT_XINTNE(0, 1);
    ASSERT_XINTNE(0, 1);
    EXPECT_XINTNE(0, 0);
    ASSERT_XINTNE(0, 0);
    EXPECT_XINTNE(0, 0);
}

TEST(metatest, assert_xintlt)
{
    EXPECT_XINTLT(0, 1);
    ASSERT_XINTLT(0, 1);
    EXPECT_XINTLT(0, 0);
    ASSERT_XINTLT(0, 0);
    EXPECT_XINTLT(0, 0);
}

TEST(metatest, assert_xintle)
{
    EXPECT_XINTLE(0, 1);
    ASSERT_XINTLE(0, 1);
    EXPECT_XINTLE(0, 0);
    ASSERT_XINTLE(0, 0);
    EXPECT_XINTLE(1, 0);
    ASSERT_XINTLE(1, 0);
    EXPECT_XINTLE(1, 0);
}

TEST(metatest, assert_xintgt)
{
    EXPECT_XINTGT(1, 0);
    ASSERT_XINTGT(1, 0);
    EXPECT_XINTGT(1, 1);
    ASSERT_XINTGT(1, 1);
    EXPECT_XINTGT(1, 1);
}

TEST(metatest, assert_xintge)
{
    EXPECT_XINTGE(1, 0);
    ASSERT_XINTGE(1, 0);
    EXPECT_XINTGE(0, 0);
    ASSERT_XINTGE(0, 0);
    EXPECT_XINTGE(0, 1);
    ASSERT_XINTGE(0, 1);
    EXPECT_XINTGE(0, 1);
}

TEST_CASE("XINT")
{
    auto test = GENERATE(                                     //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_xinteq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_xintne)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_xintlt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_xintle)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, assert_xintgt)}, //
        test_s{4, 2, &ZZT_TESTINFO(metatest, assert_xintge)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

/******************************************************************************/

TEST(metatest, streq)
{
    EXPECT_STREQ("foo", "foo");
    ASSERT_STREQ("foo", "foo");
    EXPECT_STREQ("foo", "bar");
    ASSERT_STREQ("foo", "bar");
    EXPECT_STREQ("foo", "bar");
}

TEST(metatest, strne)
{
    EXPECT_STRNE("foo", "bar");
    ASSERT_STRNE("foo", "bar");
    EXPECT_STRNE("foo", "foo");
    ASSERT_STRNE("foo", "foo");
    EXPECT_STRNE("foo", "foo");
}

TEST_CASE("STR")
{
    auto test = GENERATE(                             //
        test_s{2, 2, &ZZT_TESTINFO(metatest, streq)}, //
        test_s{2, 2, &ZZT_TESTINFO(metatest, strne)});

    auto state = RunTest(*test.test);
    REQUIRE(state.passed == test.passed);
    REQUIRE(state.failed == test.failed);
}

extern "C" int
metatest_printf(...)
{
    return 0;
}
