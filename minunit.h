#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

//define a return message with NULL
#define mu_suite_start() char *message = NULL

//define another MACRO with the same function of assert but added with log_err
#define mu_assert(test, message) if (!(test)) {\
    log_err(message); return message; }

//mu_run_test(tested function name), if successful, return NULL. Counting tests_run numbers the same time
#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

//define start main function,return test result
/* UNSOLVED: not counting the ratio of successful units, but it's just OK right now. */
#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    debug("----- RUNNING: %s", argv[0]);\
    printf("----\nRUNNING: %s\n", argv[0]);\
    char *result = name();\
    if (result != 0) {\
        printf("FAILED: %s\n", result);\
    }\
    else {\
        printf("ALL TESTS PASSED\n");\
    }\
    printf("Tests run: %d\n", tests_run);\
    exit(result != 0);\
}

int tests_run;

#endif
