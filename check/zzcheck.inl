/*
 * zztest - A test framework for crufty compilers.
 * Copyright (c) 2024 Lexi Mayfield
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include "zztest.h"

/******************************************************************************/

TEST(zzt_passing, passing)
{
    EXPECT_TRUE(1 == 1);
    EXPECT_FALSE(1 != 1);
    EXPECT_BOOLEQ(1, 2);
    EXPECT_BOOLNE(0, 1);
    EXPECT_STREQ("foo", "foo");
    EXPECT_STRNE("foo", "bar");
}

TEST(zzt_passing, passing_char)
{
    EXPECT_CHAREQ('a', 'a');
    EXPECT_CHARNE('a', 'b');
    EXPECT_CHARLT('a', 'b');
    EXPECT_CHARLE('a', 'b');
    EXPECT_CHARGT('b', 'a');
    EXPECT_CHARGE('b', 'a');
}

TEST(zzt_passing, passing_int)
{
    EXPECT_INTEQ(1, 1);
    EXPECT_INTNE(1, 2);
    EXPECT_INTLT(1, 2);
    EXPECT_INTLE(1, 2);
    EXPECT_INTGT(2, 1);
    EXPECT_INTGE(2, 1);
}

TEST(zzt_passing, passing_uint)
{
    EXPECT_UINTEQ(1, 1);
    EXPECT_UINTNE(1, 2);
    EXPECT_UINTLT(1, 2);
    EXPECT_UINTLE(1, 2);
    EXPECT_UINTGT(2, 1);
    EXPECT_UINTGE(2, 1);
}

TEST(zzt_passing, passing_xint)
{
    EXPECT_XINTEQ(1, 1);
    EXPECT_XINTNE(1, 2);
    EXPECT_XINTLT(1, 2);
    EXPECT_XINTLE(1, 2);
    EXPECT_XINTGT(2, 1);
    EXPECT_XINTGE(2, 1);
}

SUITE(zzt_passing)
{
    SUITE_TEST(zzt_passing, passing);
    SUITE_TEST(zzt_passing, passing_char);
    SUITE_TEST(zzt_passing, passing_int);
    SUITE_TEST(zzt_passing, passing_uint);
    SUITE_TEST(zzt_passing, passing_xint);
}

/******************************************************************************/

TEST(zzt_failing, failing)
{
    EXPECT_TRUE(1 == 2);
    EXPECT_FALSE(1 != 2);
    EXPECT_BOOLEQ(0, 1);
    EXPECT_BOOLNE(1, 2);
    ADD_FAILURE();
}

TEST(zzt_failing, failing_char)
{
    EXPECT_CHAREQ('a', 'b');
    EXPECT_CHARNE('a', 'a');
    EXPECT_CHARLT('b', 'b');
    EXPECT_CHARLE('b', 'b');
    EXPECT_CHARGT('a', 'b');
    EXPECT_CHARGE('a', 'b');

    EXPECT_CHAREQ('\0', '\xaa');
    EXPECT_CHAREQ('\n', '\r');
    EXPECT_CHAREQ('\t', '\\');
    EXPECT_CHAREQ(0x61, 0x62);
    EXPECT_CHAREQ(0x00, (char)0xaa);
    EXPECT_CHAREQ(0x0a, 0x0d);
    EXPECT_CHAREQ(0x09, 0x5c);
}

TEST(zzt_failing, failing_int)
{
    EXPECT_INTEQ(1, 2);
    EXPECT_INTNE(1, 1);
    EXPECT_INTLT(2, 1);
    EXPECT_INTLE(2, 1);
    EXPECT_INTGT(1, 2);
    EXPECT_INTGE(1, 2);

    EXPECT_INTEQ(1, (int)2);
}

TEST(zzt_failing, failing_uint)
{
    EXPECT_UINTEQ(1, 2);
    EXPECT_UINTNE(1, 1);
    EXPECT_UINTLT(2, 1);
    EXPECT_UINTLE(2, 1);
    EXPECT_UINTGT(1, 2);
    EXPECT_UINTGE(1, 2);

    EXPECT_UINTEQ(1, 2u);
}

TEST(zzt_failing, failing_xint)
{
    EXPECT_XINTEQ(0x1, 0x2);
    EXPECT_XINTNE(0x1, 0x1);
    EXPECT_XINTLT(0x2, 0x1);
    EXPECT_XINTLE(0x2, 0x1);
    EXPECT_XINTGT(0x1, 0x2);
    EXPECT_XINTGE(0x1, 0x2);

    EXPECT_XINTEQ(0xabc, 0x0DEF);
}

TEST(zzt_failing, failing_str)
{
    EXPECT_STREQ("foo", "bar");
    EXPECT_STREQ("\r\n", "\t\\");
    EXPECT_STREQ("f\x6F\x6F", "b\x61r");
    EXPECT_STREQ("", "The quick brown fox jumps over the lazy dog.\nLorem "
                     "ipsum dolor sit amet.");
}

SUITE(zzt_failing)
{
    SUITE_TEST(zzt_failing, failing);
    SUITE_TEST(zzt_failing, failing_char);
    SUITE_TEST(zzt_failing, failing_int);
    SUITE_TEST(zzt_failing, failing_uint);
    SUITE_TEST(zzt_failing, failing_xint);
    SUITE_TEST(zzt_failing, failing_str);
}

/******************************************************************************/

TEST(zzt_skipping, skipping) { SKIP(); }

TEST(zzt_skipping, skipping2) { SKIP(); }

SUITE(zzt_skipping)
{
    SUITE_TEST(zzt_skipping, skipping);
    SUITE_TEST(zzt_skipping, skipping2);
}

/******************************************************************************/

TEST(zzt_assert, assert_bool)
{
    ASSERT_BOOLEQ(ZZT_TRUE, ZZT_FALSE);
    EXPECT_BOOLEQ(ZZT_FALSE, ZZT_TRUE);
}

TEST(zzt_assert, assert_char)
{
    ASSERT_CHAREQ('a', 'b');
    EXPECT_CHAREQ('c', 'd');
}

TEST(zzt_assert, assert_int)
{
    ASSERT_INTEQ(1, 2);
    EXPECT_INTEQ(3, 4);
}

TEST(zzt_assert, assert_uint)
{
    ASSERT_UINTEQ(1, 2);
    EXPECT_UINTEQ(3, 4);
}

TEST(zzt_assert, assert_xint)
{
    ASSERT_XINTEQ(1, 2);
    EXPECT_XINTEQ(3, 4);
}

TEST(zzt_assert, assert_str)
{
    ASSERT_STREQ("foo", "bar");
    EXPECT_STREQ("baz", "plugh");
}

SUITE(zzt_assert)
{
    SUITE_TEST(zzt_assert, assert_bool);
    SUITE_TEST(zzt_assert, assert_char);
    SUITE_TEST(zzt_assert, assert_int);
    SUITE_TEST(zzt_assert, assert_uint);
    SUITE_TEST(zzt_assert, assert_xint);
    SUITE_TEST(zzt_assert, assert_str);
}

/******************************************************************************/

int
main()
{
    ADD_TEST_SUITE(zzt_passing);
    ADD_TEST_SUITE(zzt_failing);
    ADD_TEST_SUITE(zzt_skipping);
    ADD_TEST_SUITE(zzt_assert);

    return RUN_TESTS();
}
