#include "minunit.h"
#include <dlfcn.h>

//static libfile pwd
const char* lib_file = "build/libtest_LIBRARY.so";
void *lib = NULL;
//lib dunction prototype
typedef int (*lib_function) (const char *data);

//call all normal functions in the library
int check_functions(const char *func_to_run, const char *data, int expected)
{
    //find function in the library
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find function: %s in library: %s. ERROR: %s", func_to_run, lib_file, dlerror());

    //run the function and check return code
    int rc = func(data);
    check(rc == expected, "Funtion %s returned %d for data: %s", func_to_run, rc, data);

    return 0;
error:
    return 1;

}

//test prerequiste function
char *test_dlopen()
{
    lib = dlopen(lib_file, RTLD_LAZY);
    mu_assert(lib != NULL, "Failed to open the library.");

    return NULL;
}

//test all normal lib functions
char *test_functions()
{
    mu_assert(check_functions("print_a_message", "hello", 0) == 0, "print_a_message failed.");
    mu_assert(check_functions("uppercase", "hello", 0) == 0, "uppercase failed.");
    mu_assert(check_functions("lowercase", "HELLO", 0) == 0, "lowercase failed.");

    return NULL;
}

//on purpose failure functions test
char *test_failures()
{
    mu_assert(check_functions("fail_on_purpose", "hello, failuer test.", 1) == 0, "Failure test failed.");

    return NULL;
}

//test close section functions
char *test_dlclose()
{
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close the tested lib.");

    return NULL;
}

//entrance of all test units
char *all_tests()
{
    //init the variable message
    mu_suite_start();

    mu_run_test(test_dlopen);
    mu_run_test(test_functions);
    mu_run_test(test_failures);
    mu_run_test(test_dlclose);

    return NULL;
}

//init test
RUN_TESTS(all_tests);
