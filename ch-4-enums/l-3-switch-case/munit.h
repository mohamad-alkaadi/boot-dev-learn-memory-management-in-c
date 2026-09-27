#ifndef MUNIT_H
#define MUNIT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  MUNIT_FAIL = 0,
  MUNIT_OK   = 1,
  MUNIT_SKIP = 2
} MunitResult;

typedef struct MunitTest_ MunitTest;
typedef struct MunitSuite_ MunitSuite;

typedef MunitResult (* MunitTestFunc)(const void* params, void* user_data);

struct MunitTest_ {
  char* name;
  MunitTestFunc test;
  void* (* setup)(const void* params, void* user_data);
  void (* tear_down)(void* fixture);
  int options;
  void* parameters;
};

struct MunitSuite_ {
  char* prefix;
  MunitTest* tests;
  MunitSuite* suites;
  unsigned int iterations;
  int options;
};

/* Core Test Runner API */
int munit_suite_main(const MunitSuite* suite, void* user_data, int argc, char* const* argv);
MunitSuite munit_suite(char* prefix, MunitTest* tests);

/* Boot.dev Helper Macros for Test Cases */
#define munit_case(type, name, body) \
  static MunitResult name(const void* params, void* user_data) { \
    (void)params; \
    (void)user_data; \
    body; \
    return MUNIT_OK; \
  }

#define munit_test(name, func) \
  { (char*)(name), func, NULL, NULL, 0, NULL }

#define munit_null_test \
  { NULL, NULL, NULL, NULL, 0, NULL }

/* Core Assertion Macros */
#define munit_assert(expr) \
  do { \
    if (!(expr)) { \
      fprintf(stderr, "Assertion failed: %s at %s:%d\n", #expr, __FILE__, __LINE__); \
      return MUNIT_FAIL; \
    } \
  } while (0)

#define munit_assert_string_equal(a, b) \
  do { \
    const char* _a = (a); \
    const char* _b = (b); \
    if (_a == NULL || _b == NULL || strcmp(_a, _b) != 0) { \
      fprintf(stderr, "String assertion failed at %s:%d: expected \"%s\", got \"%s\"\n", \
              __FILE__, __LINE__, _b ? _b : "NULL", _a ? _a : "NULL"); \
      return MUNIT_FAIL; \
    } \
  } while (0)

#define assert_string_equal(a, b, msg) munit_assert_string_equal(a, b)
#define assert_int_equal(a, b, msg)    munit_assert((a) == (b))
#define assert_true(expr, msg)         munit_assert(expr)
#define assert_false(expr, msg)        munit_assert(!(expr))

#ifdef __cplusplus
}
#endif

#endif /* MUNIT_H */
