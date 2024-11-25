#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>

static jmp_buf escape;

static void
test_abort(void)
{
    longjmp(escape, 1);
}

#define BUF_ABORT test_abort()
#include "buf.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++; \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            count_fail++; \
        } \
    } while (0)

static uint32_t
pcg32(uint64_t *s)
{
    uint64_t m = 0x5851f42d4c957f2d;
    uint64_t a = 0x8b260b70b8e98891;
    uint64_t p = *s;
    uint32_t x = ((p >> 18) ^ p) >> 27;
    uint32_t r = p >> 59;
    *s = p * m + a;
    return (x >> r) | (x << (-r & 31u));
}

static unsigned long
bench(uint64_t *rng)
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
uint64_t
uepoch(void)
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
uint64_t
uepoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif

int
main(int argc, char **argv)
{
    /* Benchtest? */
#if TEST_COMMAND==0
    if (argc > 1) {
        uint64_t rng = strtoull(argv[1], 0, 16);
        unsigned long r = 0;
        uint64_t start = uepoch();
        for (int i = 0; i < 300; i++)
            r += bench(&rng);
        double t = (uepoch() - start) / 1e6;
        printf("%.6gs : actual %lu, expect 428859598\n", t, r);
        return 0;
    } else {
        return 1;
    }
#endif
    /* volatile due to setjmp() / longjmp() */
    volatile int count_pass = 0;
    volatile int count_fail = 0;
    int flag = 0;

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

    printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0 && flag == 1;
    //}
}
