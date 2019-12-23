#include "../tests.h"

extern char	*binary_file_params[];

// static void
// *test_setup(const MunitParameter params[], MUNIT_UNUSED void *data) {
// 	struct fixture *s = malloc(sizeof(struct fixture));
// 	return (void*)s;
// }

// static void
// test_teardown(void *fixture) {
// }

static MunitResult
test_otool_main_binary_files(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	// char *argv[2] = { "./ft_otool", "test/artifacts/binary/main32" };

	munit_assert_int(1, ==, 1);
	return EXIT_SUCCESS;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_otool_main_binary_files", test_otool_main_binary_files, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite otool_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/macho/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
