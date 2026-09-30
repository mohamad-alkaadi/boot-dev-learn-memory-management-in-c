#ifndef MUNIT_H
#define MUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef void (*MunitTestFunc)(void);

typedef struct {
    const char *name;
    MunitTestFunc func;
} MunitTest;

typedef struct {
    const char *prefix;
    MunitTest *tests;
} MunitSuite;

#define munit_case(type, name, body) \
    static void name(void) body

#define munit_test(name, func) \
    { name, func }

#define munit_null_test { NULL, NULL }

static inline MunitSuite munit_suite(const char *prefix, MunitTest *tests) {
    MunitSuite suite = { prefix, tests };
    return suite;
}

#define munit_assert_size(a, op, b, msg) \
    if (!((a) op (b))) { \
        printf("Assertion failed: %s (size %zu " #op " %zu)\n", msg, (size_t)(a), (size_t)(b)); \
        exit(1); \
    }

#define munit_assert_uint16(a, op, b, msg) \
    if (!((a) op (b))) { \
        printf("Assertion failed: %s (0x%04X " #op " 0x%04X)\n", msg, (uint16_t)(a), (uint16_t)(b)); \
        exit(1); \
    }

#define munit_assert_uint32(a, op, b, msg) \
    if (!((a) op (b))) { \
        printf("Assertion failed: %s (0x%08X " #op " 0x%08X)\n", msg, (uint32_t)(a), (uint32_t)(b)); \
        exit(1); \
    }

#define munit_assert_uint8(a, op, b, msg) \
    if (!((a) op (b))) { \
        printf("Assertion failed: %s (0x%02X " #op " 0x%02X)\n", msg, (uint8_t)(a), (uint8_t)(b)); \
        exit(1); \
    }

static inline int munit_suite_main(MunitSuite *suite, void *user_data, int argc, char * const *argv) {
    (void)user_data;
    (void)argc;
    (void)argv;
    
    printf("Running suite: %s\n", suite->prefix);
    int passed = 0;
    
    for (int i = 0; suite->tests[i].name != NULL; i++) {
        printf("  Running %s... ", suite->tests[i].name);
        suite->tests[i].func();
        printf("PASSED\n");
        passed++;
    }
    
    printf("\nAll %d tests passed successfully.\n", passed);
    return 0;
}

#endif // MUNIT_H
