/**
 * @mainpage
 *
 * This program is controlled by the TEST_COMMAND environment variable,
 * initialized before compiling the program with a value from 0 to 21, to select a specific test.
 * This program is initialized with the value 0.
 *
 * The following tests are available:
 *
 * @li **0** - Benchmark.
 * @li **1** - Buffer volume test.
 * @li **2** - Buffer size test.
 * @li **3** - Test for the buffer size after making an element.
 * @li **4** - Test for the correct value of this element.
 * @li **5** - Buffer cleaning test.
 * @li **6** - Test whether the buffer is not released.
 * @li **7** - Test for freeing up memory for the buffer.
 * @li **8** - Test for the size of the freed buffer.
 * @li **9** - Test for the value of the pointer of the freed buffer.
 * @li **10** - Size test for 10,000 items.
 * @li **11** - Test for the correct element search.
 * @li **12** - Buffer size increase test.
 * @li **13** - Memory size test after buffer grow.
 * @li **14** - Buffer Truncation test.
 * @li **15** - Tests for adding and removing using push buffer.
 * @li **16** - Tests for adding and removing using pop buffer.
 * @li **17-21** - Tests for adding and removing using push and pop buffers.
 */

/**
 * @file tests.c
 * @brief Test suite for the dynamic buffer operations.
 * 
 * This file contains a test suite for the buffer functions defined in "buf.h".
 * The tests validate various operations like initialization, push, pop, growth, truncation,
 * and error handling for memory allocation failures. Additionally, the file includes a
 * benchmarking functionality to assess the performance of the buffer operations.
 *
 * @section test_macros Macros:
 * - `TEST(s, x)` : Runs a test for the condition `x`, printing "PASS" or "FAIL" with the test name `s`.
 * 
 * @section platform_specific Platform-specific code:
 * - On Windows, colors are not used for output, while on other platforms ANSI escape codes are used.
 * 
 * @section test_command_conditional Compilation flags
 * - `TEST_COMMAND` is used to control which test to execute. The value of `TEST_COMMAND` determines
 *   which specific test is compiled and run.
 *
 * The tests are designed to run as part of the command-line application or as specific unit tests
 * when the macro `TEST_COMMAND` is set to the corresponding test number.
 * 
 * @note This test suite is volatile due to the use of setjmp() and longjmp() for error handling in
 *       case of memory allocation failures.
 */

#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <libintl.h>
#include <libgen.h>
#include <locale.h>

static jmp_buf escape; /**< Used for setjmp()/longjmp() error handling. */

#define _(STRING) gettext(STRING) /**< Macro for translation using gettext */

/**
 * @brief Aborts the program by calling longjmp().
 * 
 * This function is used for error handling when a memory allocation fails during
 * buffer operations. It triggers longjmp to exit the test with an error condition.
 */
static void test_abort(void) 
{
    longjmp(escape, 1);
}

/** @brief Override of BUF_ABORT to call test_abort(). */
#define BUF_ABORT test_abort()
#include "buf.h"

/** @brief Define color macros based on platform. */
#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

/** 
 * @brief Macro for testing conditions.
 * 
 * This macro prints the result of a test. If the test passes, it prints "PASS" in green,
 * and if it fails, it prints "FAIL" in red. The test result is based on the condition `x`.
 * 
 * @param s The name of the test.
 * @param x The condition to test.
 */

#define TEST(s, x) \
    do { \
        if (x) { \
            printf("\033[32;1m %s %s\n \033[0m", _("PASS"), s); \
            count_pass++; \
        } else { \
            printf("\033[31;1m %s %s\n \033[0m", _("FAIL"), s); \
            count_fail++; \
        } \
    } while (0)

/**
 * @brief PCG32 random number generator.
 * 
 * This function implements a PCG32 random number generator based on a 64-bit state.
 * It produces random 32-bit values based on the provided state.
 * 
 * @param s A pointer to the random state (64-bit).
 * @return A random 32-bit value.
 */
static uint32_t pcg32(uint64_t *s)
{
    uint64_t m = 0x5851f42d4c957f2d;
    uint64_t a = 0x8b260b70b8e98891;
    uint64_t p = *s;
    uint32_t x = ((p >> 18) ^ p) >> 27;
    uint32_t r = p >> 59;
    *s = p * m + a;
    return (x >> r) | (x << (-r & 31u));
}

/**
 * @brief Benchmarks the buffer performance by generating random values.
 * 
 * This function uses the PCG32 RNG to generate random values and stores them in a buffer.
 * It then compares the generated values against a threshold and returns the number of values
 * exceeding the threshold.
 * 
 * @param rng A pointer to the random number generator state (64-bit).
 * @return The number of values exceeding the threshold.
 */
static unsigned long bench(uint64_t *rng)
{
    unsigned long r = 0;
    uint32_t n = 1000000 + pcg32(rng) % 4000000;
    float *buf = 0;

    for (uint32_t i = 0; i < n; i++)
        buf_push(buf, pcg32(rng) / (double)UINT32_MAX);

    float threshold = pcg32(rng) / (double)UINT32_MAX;
    for (uint32_t i = 0; i < n; i++)
        r += buf[i] > threshold;

    buf_free(buf);
    return r;
}

#ifdef _WIN32
#include <windows.h>
/**
 * @brief Returns the current time in microseconds on Windows.
 * 
 * This function retrieves the system's current time in microseconds since the Unix epoch.
 * 
 * @return The current time in microseconds.
 */
uint64_t uepoch(void)
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t tt = ft.dwHighDateTime;
    tt <<= 32;
    tt |= ft.dwLowDateTime;
    tt /=10;
    tt -= UINT64_C(11644473600000000);
    return tt;
}
#else
#include <sys/time.h>
/**
 * @brief Returns the current time in microseconds on Unix-based systems.
 * 
 * This function retrieves the system's current time in microseconds since the Unix epoch.
 * 
 * @return The current time in microseconds.
 */
uint64_t uepoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif

/**
 * @brief Main function to execute the tests.
 * 
 * This function runs the tests based on the `TEST_COMMAND` macro. Depending on the value
 * of `TEST_COMMAND`, different buffer operations (e.g., push, pop, grow, truncation) are tested.
 * It also includes a benchmark section that runs a performance test of the buffer operations.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int main(int argc, char **argv) {
    int opt;
// Определение длинных опций
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    // Обработка опций
    while ((opt = getopt_long(argc, argv, "r", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                // Параметр --help
                printf(_("This program is controlled by the TEST_COMMAND environment variable,\n\
                initialized before compiling the program with a value from 0 to 21, to select a specific test. This program is initialized with the value %d.\n\
                0 - benchmark.\n\
                1 - Buffer volume test\n\
                2 - Buffer size test\n\
                3 - Test for the buffer size after making an element\n\
                4 - Test for the correct value of this element\n\
                5 - Buffer cleaning test\n \
                6 - Test whether the buffer is not released\n \
                7 - Test for freeing up memory for the buffer\n \
                8 - Test for the size of the freed buffer\n \
                9 - Test for the value of the pointer of the freed buffer\n \
                10 - Size test for 10,000 items\n \
                11 - Test for the correct element search\n \
                12 - Buffer size increase test\n \
                13 - Memory size test after buffer grow\n \
                14 - Buffer Truncation test\n \
                15-21 - Tests for adding and removing using push and pop buffers.\n  --help  Display this help message.\n"), TEST_COMMAND);
                return 0;
            case 'v':
                // Параметр -v
                printf("v1.0.0\n");
                return 0;

            case '?':
                // Обработка ошибок или неизвестных опций
                return 1;
        }
    }
    /* Benchtest? */
#if TEST_COMMAND==0
    if (argc > 1) {
        uint64_t rng = strtoull(argv[1], 0, 16);
        unsigned long r = 0;
        uint64_t start = uepoch();
        for (int i = 0; i < 300; i++)
            r += bench(&rng);
        double t = (uepoch() - start) / 1e6;
        printf(_("%.6gs : actual %lu, expect 428859598\n"), t, r);
        return 0;
    } else {
        return 1;
    }
#endif
    /* volatile due to setjmp() / longjmp() */
    volatile int count_pass = 0;  /**< Number of passed tests. */
    volatile int count_fail = 0; /**< Number of failed tests. */

    int flag = 0; /**< Flag for tracking if tests are running. */

    //if (setjmp(escape))
    //    abort();

    /* initialization, buf_free() */
    float *a = 0;
#if TEST_COMMAND == 1
    flag = 1;
    TEST("capacity init", buf_capacity(a) == 0);
#elif TEST_COMMAND == 2
    flag = 1;
    TEST("size init", buf_size(a) == 0);
#endif

    buf_push(a, 1.3f);

#if TEST_COMMAND == 3
    flag = 1;
    TEST("size 1", buf_size(a) == 1);
#elif TEST_COMMAND == 4
    flag = 1;
    TEST("value", a[0] == (float)1.3f);
#endif
    buf_clear(a);

#if TEST_COMMAND == 5
    flag = 1;
    TEST("clear", buf_size(a) == 0);
#elif TEST_COMMAND == 6
    flag = 1;
    TEST("clear not-free", a != 0);
#endif

    buf_free(a);

#if TEST_COMMAND == 7
    flag = 1;
    TEST("free", a == 0);
#endif

    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);

#if TEST_COMMAND == 8
    flag = 1;
    TEST("clear empty", buf_size(a) == 0);
#elif TEST_COMMAND == 9
    flag = 1;
    TEST("clear no-op", a == 0);
#endif

    /* buf_push(), [] operator */
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);

#if TEST_COMMAND == 10
    flag = 1;
    TEST("size 10000", buf_size(ai) == 10000);
#endif
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;

#if TEST_COMMAND == 11
    flag = 1;
    TEST("match 10000", match == 10000);
#endif
    buf_free(ai);

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
#if TEST_COMMAND == 12
    flag = 1;
    TEST("grow 1000", buf_capacity(ai) == 1000);
#elif TEST_COMMAND == 13
    flag = 1;
    TEST("size 0 (grow)", buf_size(ai) == 0);
#endif

    buf_trunc(ai, 100);

#if TEST_COMMAND == 14
    flag = 1;
    TEST("trunc 100", buf_capacity(ai) == 100);
#endif
    buf_free(ai);

    /* buf_pop() */
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
#if TEST_COMMAND == 15
    flag = 1;
    TEST("size 4", buf_size(a) == 4);
#elif TEST_COMMAND == 16
    flag = 1;
    TEST("pop 3", buf_pop(a) == (float)1.4f);
#endif
    buf_trunc(a, 3);

#if TEST_COMMAND == 17
    flag = 1;
    TEST("size 3", buf_size(a) == 3);
#elif TEST_COMMAND == 18
    flag = 1;
    TEST("pop 2", buf_pop(a) == (float)1.3f);
#elif TEST_COMMAND == 19
    flag = 1;
    buf_pop(a);
    TEST("pop 1", buf_pop(a) == (float)1.2f);
#elif TEST_COMMAND == 20
    flag = 1;
    buf_pop(a);
    buf_pop(a);
    TEST("pop 0", buf_pop(a) == (float)1.1f);
#elif TEST_COMMAND == 21
    flag = 1;
    buf_pop(a);
    buf_pop(a);
    buf_pop(a);
    TEST("size 0 (pop)", buf_size(a) == 0);
#endif
    buf_free(a);

    /* Memory allocation failures */

    /*
    volatile int aborted;

    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            size_t max = (PTRDIFF_MAX - sizeof(struct buf)) / sizeof(*p) + 1;
            buf_grow(p, max);
            buf_grow(p, max);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("out of memory", aborted);
    }

    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("overflow init", aborted);
    }
    */

    /*
    {
        int *volatile p = 0;
        aborted = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, 1);
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        TEST("overflow grow", aborted);
    }
    */

    printf(_("%d fail, %d pass\n"), count_fail, count_pass);
    return count_fail != 0 && flag == 1;
    //}
}
