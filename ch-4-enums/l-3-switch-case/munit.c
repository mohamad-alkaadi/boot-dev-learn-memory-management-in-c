#include "munit.h"

MunitSuite munit_suite(char* prefix, MunitTest* tests) {
    MunitSuite suite;
    suite.prefix = prefix;
    suite.tests = tests;
    suite.suites = NULL;
    suite.iterations = 1;
    suite.options = 0;
    return suite;
}

int munit_suite_main(const MunitSuite* suite, void* user_data, int argc, char* const* argv) {
    (void)user_data;
    (void)argc;
    (void)argv;

    if (suite == NULL || suite->tests == NULL) {
        fprintf(stderr, "Error: Invalid test suite\n");
        return 1;
    }

    int passed = 0;
    int failed = 0;

    printf("Running test suite: %s\n", suite->prefix ? suite->prefix : "default");
    printf("========================================\n");

    for (size_t i = 0; suite->tests[i].name != NULL && suite->tests[i].test != NULL; i++) {
        MunitTest test = suite->tests[i];
        printf("Running %s... ", test.name);

        MunitResult result = test.test(test.parameters, NULL);

        if (result == MUNIT_OK) {
            printf("[OK]\n");
            passed++;
        } else {
            printf("[FAILED]\n");
            failed++;
        }
    }

    printf("========================================\n");
    printf("Results: %d passed, %d failed\n", passed, failed);

    return (failed == 0) ? 0 : 1;
}
