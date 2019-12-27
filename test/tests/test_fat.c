#include "../tests.h"

extern int	g_header_calls;
extern int	g_segment_calls;
extern int	g_lc_calls;
extern int	g_section_calls;

static MunitResult
test_dump_fat_bin_dumps(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/fat/fatbin" };
	t_dump_fxs funcs = { verify_header64, verify_segments, verify_sections, verify_load_command };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(ctx.file, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(dump_fat_bin(ctx.file, &ctx, &funcs), ==, EXIT_SUCCESS);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	munit_assert_int(g_header_calls, ==, 1);
	munit_assert_int(g_segment_calls, ==, 4);
	munit_assert_int(g_lc_calls, ==, 11);
	munit_assert_int(g_section_calls, ==, 7);
	g_section_calls = 0;
	g_lc_calls = 0;
	g_segment_calls = 0;
	g_header_calls = 0;
	return EXIT_SUCCESS;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_dump_fat_bin_dumps", test_dump_fat_bin_dumps, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_fat_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/fat/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
