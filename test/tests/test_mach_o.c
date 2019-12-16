#include "../tests.h"
#include <inttypes.h>

extern int	g_header_calls;
extern int	g_segment_calls;
extern int	g_lc_calls;
extern int	g_section_calls;

static MunitResult	test_dump_macho_bin_dumps_mach_32(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_fxs funcs = {verify_header, verify_segments, verify_sections, verify_load_command };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_int(dump_macho_bin(ctx.file, &ctx, &funcs), ==, EXIT_SUCCESS);
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

static MunitResult	test_mach32_segment_addr(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_fxs funcs = { NULL, verify_segment_address, NULL, NULL	};

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_int(dump_macho_bin(ctx.file, &ctx, &funcs), ==, EXIT_SUCCESS);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	munit_assert_int(g_segment_calls, ==, 1);
	g_segment_calls = 0;
	return EXIT_SUCCESS;
}

static MunitResult	test_mach32_section_addr(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_fxs funcs = { NULL, NULL, verify_section_address, NULL	};

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_int(dump_macho_bin(ctx.file, &ctx, &funcs), ==, EXIT_SUCCESS);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	munit_assert_int(g_section_calls, ==, 1);
	g_section_calls = 0;
	return EXIT_SUCCESS;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_dump_macho_bin_dumps_mach_32", test_dump_macho_bin_dumps_mach_32, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_mach32_segment_addr", test_mach32_segment_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_mach32_section_addr", test_mach32_section_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_macho_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/macho/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
