zztest
======
A tiny unit test framework for resource-constrained environments and crufty
C/C++ compilers.

Why?
----
I find myself hacking on old codebases from the 90's quite a bit, and I wanted
a unit test framework that I could use for testing [kruft][1].  From there,
I...kind of went overboard, just to see if I could.

Later, I realized that a test suite small enough for running tests in C
compilers for DOS from 1991 was also small enough to run in modern embedded
contexts, in environments where test runners like Google Test are a poor fit.

Tested Compilers
----------------
- Modern GCC, Clang, MSVC
- Microsoft Visual C++ 6.0
- Borland C++ 3.1 (DOS)
- Watcom C 9.01 (DOS)

How to Use
----------
zztest is self-contained.  You can either drop `zztest.c` and `zztest.h`
into your project and use them directly, or use the included `CMakeLists.txt`
to build and link against the library separately.

The interface and output is intentionally similar to Google Test, though
the fact that zztest is written in C necessitates some differences.

### A Short Example
```c
/*
 * Tests are defined using the TEST macro.  First param is the suite name
 * second param is the test name.  Both params must be valid C identifiers.
 */
TEST(my_suite, test_one)
{
    /*
     * REQUIRE macros halt the test if the condition fails.
     *
     * Because C doesn't support overloading, REQUIRE is not a single macro,
     * but an entire suite of them.  This allows useful error messages that
     * are specific about the failing condition if a test fails.
     */

    REQUIRE_TRUE(1 == 1);     /* Requires a truthy evaluation */
    REQUIRE_CHAREQ('a', 'a'); /* Requires two chars to be equal */
    REQUIRE_INTLT(1, 2);      /* Requires the left int to be less than the right */
}

TEST(my_suite, test_two)
{
    /*
     * EXPECT macros signal a test failure if the condition fails, but allows
     * test execution to continue.
     */

    EXPECT_FALSE(1 != 1); /* Expects a falsy evaluation */
    EXPECT_UINTGE(2, 1);  /* Expects the left uint to be greater than or equal to the right */
    EXPECT_XINTNE(1, 2);  /* Expects two uints to be unequal, prints values as hex if not */
}

/*
 * Unlike test frameworks written in C++, zztest test suites must be defined
 * by hand.  This set of macros creates a linked list that allows the test
 * runner to iterate through all of the tests when the suite is run.
 */
SUITE(my_suite)
{
    SUITE_TEST(my_suite, test_one);
    SUITE_TEST(my_suite, test_two);
}

/*
 * Entry point for the test runner.
 */
int main()
{
    ADD_TEST_SUITE(zztest);
    return RUN_TESTS();
}
```

Configuration
-------------
Here are the various defines you can use to customize the functionality of
zztest:

| Define | Default | Explanation |
| ------ | ------- | ----------- |
| `ZZTEST_CONFIG_PRINTF` | `printf` | Uses this function to print test suite results. |

Note that as of this moment, zztest does not use `malloc` anywhere in the
implementation, so no allocator override is necessary.

License
-------
Boost Software License.

[1]: https://github.com/leximayfield/kruft
