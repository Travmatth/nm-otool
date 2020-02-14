#include "tests.h"

extern MunitSuite common_format_suite;
extern MunitSuite common_utils_suite;
extern MunitSuite common_macho_suite;
extern MunitSuite mach_print_suite;
extern MunitSuite common_fat_suite;
extern MunitSuite otool_suite;

static MunitSuite test_suites = {
	//{ name, tests, suites, iterations, options },
    "/nm-otool", NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char **argv)
{
    MunitSuite *suites = calloc(7, sizeof(MunitSuite));
    suites[0] = common_format_suite;
    suites[1] = common_utils_suite;
    // suites[2] = common_macho_suite;
    // suites[3] = mach_print_suite;
    // suites[4] = common_fat_suite;
    // suites[5] = otool_suite;

    test_suites.suites = suites;
    int ret = munit_suite_main(&test_suites, NULL, argc, argv);
    free(suites);
    return ret;
}
