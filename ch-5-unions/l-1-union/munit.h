
#ifndef MUNIT_H
#define MUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int total;
    int passed;
    int failed;
} MunitSuiteState;

static MunitSuiteState g_munit_state = {0, 0, 0};

#define munit_case(type, name, body) \
    static void name(void) body

#define munit_test(path, func_ptr) \
    { path, func_ptr }

typedef struct {
    const char *name;
    void (*func)(void);
} MunitTest;

typedef struct {
    const char *prefix;
    MunitTest *tests;
} MunitSuite;

#define munit_null_test { NULL, NULL }

/* --- Assertion Helpers --- */

static inline void munit_assert_string_equal(const char *expected, const char *actual, const char *msg) {
    g_munit_state.total++;
    if (expected && actual && strcmp(expected, actual) == 0) {
        g_munit_state.passed++;
    } else {
        g_munit_state.failed++;
        printf(" [FAIL] %s\n", msg ? msg : "String mismatch");
        printf("   Expected: \"%s\"\n", expected ? expected : "NULL");
        printf("   Actual:   \"%s\"\n", actual ? actual : "NULL");
    }
}

#define assert_string_equal(expected, actual, msg) \
    munit_assert_string_equal(expected, actual, msg)

#define assert_int_equal(expected, actual, msg) do { \
    g_munit_state.total++; \
    if ((expected) == (actual)) { \
        g_munit_state.passed++; \
    } else { \
        g_munit_state.failed++; \
        printf(" [FAIL] %s\n   Expected: %d\n   Actual:   %d\n", \
               (msg) ? (msg) : "Integer mismatch", (int)(expected), (int)(actual)); \
    } \
} while(0)

#define assert_true(expr, msg) do { \
    g_munit_state.total++; \
    if (expr) { \
        g_munit_state.passed++; \
    } else { \
        g_munit_state.failed++; \
        printf(" [FAIL] %s\n   Expression evaluated to false.\n", (msg) ? (msg) : "Assertion failed"); \
    } \
} while(0)

/* --- Runner Infrastructure --- */

static inline MunitSuite munit_suite(const char *name, MunitTest *tests) {
    MunitSuite suite = { name, tests };
    return suite;
}

static inline int munit_suite_main(MunitSuite *suite, void *user_data, int argc, char * const *argv) {
    (void)user_data;
    (void)argc;
    (void)argv;

    printf("Running test suite: %s\n", suite->prefix ? suite->prefix : "default");
    printf("========================================\n");

    for (size_t i = 0; suite->tests[i].name != NULL && suite->tests[i].func != NULL; i++) {
        printf("Running %s ...", suite->tests[i].name);
        int failed_before = g_munit_state.failed;
        suite->tests[i].func();
        if (g_munit_state.failed == failed_before) {
            printf(" OK\n");
        }
    }

    printf("========================================\n");
    printf("Tests Run: %d | Passed: %d | Failed: %d\n",
           g_munit_state.total, g_munit_state.passed, g_munit_state.failed);

    return (g_munit_state.failed == 0) ? 0 : 1;
}

#endif /* MUNIT_H */
