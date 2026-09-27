#ifndef MUNIT_H
#define MUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Micro-unit Result Statuses
typedef enum {
    MUNIT_OK,
    MUNIT_FAIL,
    MUNIT_SKIP
} MunitResult;

// Basic test function signature
typedef MunitResult (*MunitTestFunc)(const void* params, void* user_data);

// Test structure definitions
typedef struct {
    char* name;
    MunitTestFunc test;
    void* (*setup)(const void* params, void* user_data);
    void (*tear_down)(void* fixture);
    int options;
    void* parameters;
} MunitTest;

typedef struct MunitSuite_ MunitSuite;
struct MunitSuite_ {
    char* prefix;
    MunitTest* tests;
    MunitSuite* suites;
    unsigned int iterations;
    int options;
};

// Standard null terminator for test arrays
#define munit_null_test { NULL, NULL, NULL, NULL, 0, NULL }

// Wrapper for suite construction
static inline MunitSuite munit_suite(char* name, MunitTest* tests) {
    MunitSuite suite = { name, tests, NULL, 1, 0 };
    return suite;
}

static inline MunitTest munit_test(char* name, MunitTestFunc test) {
    MunitTest t = { name, test, NULL, NULL, 0, NULL };
    return t;
}

// Assertion Macros
#define assert_int(a, op, b, msg) \
    do { \
        int _a = (a); \
        int _b = (b); \
        if (!(_a op _b)) { \
            fprintf(stderr, "[FAIL] %s:%d: Assertion failed (%s %s %s -> %d %s %d): %s\n", \
                    __FILE__, __LINE__, #a, #op, #b, _a, #op, _b, msg); \
            return MUNIT_FAIL; \
        } \
    } while (0)

#define assert_true(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "[FAIL] %s:%d: Assertion failed: " #expr "\n", __FILE__, __LINE__); \
            return MUNIT_FAIL; \
        } \
    } while (0)

// Boot.dev specific test macro convenience wrapper
#define RUN 0
#define SUBMIT 1

#define munit_case(type, name, code) \
    MunitResult name(const void* params, void* user_data) { \
        (void)params; \
        (void)user_data; \
        code \
        return MUNIT_OK; \
    }

// Minimal runner function to execute test cases
static inline int munit_suite_main(const MunitSuite* suite, void* user_data, int argc, char* const* argv) {
    (void)user_data; (void)argc; (void)argv;
    int failed = 0;
    int passed = 0;

    printf("Running suite: %s\n", suite->prefix);
    for (size_t i = 0; suite->tests[i].name != NULL; i++) {
        MunitTest t = suite->tests[i];
        printf("  Running test %s... ", t.name);
        MunitResult res = t.test(NULL, NULL);
        if (res == MUNIT_OK) {
            printf("OK\n");
            passed++;
        } else {
            failed++;
        }
    }

    printf("\nResults: %d passed, %d failed\n", passed, failed);
    return failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

#endif // MUNIT_H
