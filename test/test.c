#include "tests.h"

extern MunitSuite common_format_suite;
extern MunitSuite mach_print_suite;
extern MunitSuite common_utils_suite;

static MunitSuite test_suites = {
	//{ name, tests, suites, iterations, options },
    "/nm-otool", NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char **argv)
{
    MunitSuite *suites = calloc(4, sizeof(MunitSuite));
    suites[0] = common_format_suite;
    suites[1] = mach_print_suite;
    suites[2] = common_utils_suite;

    test_suites.suites = suites;
    int ret = munit_suite_main(&test_suites, NULL, argc, argv);
    free(suites);
    return ret;
}
