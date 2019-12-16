#include "../tests.h"

static int	g_header_calls = 0;
static int	g_segment_calls = 0;
static int	g_lc_calls = 0;
static int	g_section_calls = 0;

/*
	verify dumping header, load commands, segments and sections of a mach-o 32 bit binary
*/

static int		verify_segments(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
	(void)file;
	(void)ctx;
	(void)segment;
	(void)segment_64;
	g_segment_calls += 1;
	return EXIT_SUCCESS;
}

static int		verify_load_command(char *file, t_ctx *ctx, struct load_command *lc, void *addr) {
	(void)file;
	(void)ctx;
	(void)lc;
	(void)addr;
	g_lc_calls += 1;
	return EXIT_SUCCESS;
}

static int		verify_sections(char *file, t_ctx *ctx, struct section *section, struct section_64 *section_64) {
	(void)file;
	(void)ctx;
	(void)section;
	(void)section_64;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

/*
	verify segment address of mach-o 32 bit binary is correct
*/

// static int		verify_segment_address(t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
// 	(void)segment_64;
// 	if (!strcmp(segment->segname, "__TEXT")) {
// 		uint32_t magic = *(uint32_t *)ctx->file + segment->fileoff;
// 		if (magic == MH_MAGIC)
// 			g_segment_calls += 1;
// 	}
// 	return EXIT_SUCCESS;
// }

/*
	verify section address of mach-o 32 bit binary is correct
*/

// static int		verify_section_address(t_ctx *ctx, struct section *sect, struct section_64 *sect64) {
// 	(void)sect64;
// 	if (!strcmp("__text", sect->sectname)) {
// 		uint64_t val = *(uint64_t*)(ctx->file + sect->offset);
// 		if (val == 0x00E818EC83E58955ULL)
// 			g_section_calls += 1;
// 	}
// 	return EXIT_SUCCESS;
// }

static int		verify_header(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)file;
	(void)ctx;
	(void)header_64;
	if (header) {
		if (header->magic == MH_MAGIC)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

static MunitResult	test_dump_fat_bin_dumps(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_obj_fat.o" };
	t_dump_fxs funcs = {
		verify_header,
		verify_segments,
		verify_sections,
		verify_load_command
	};

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_int(dump_fat_bin(ctx.file, &ctx, &funcs), ==, EXIT_SUCCESS);
	// if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
	// 	return MUNIT_ERROR;
	// munit_assert_int(g_header_calls, ==, 1);
	// munit_assert_int(g_segment_calls, ==, 4);
	// munit_assert_int(g_lc_calls, ==, 11);
	// munit_assert_int(g_section_calls, ==, 7);
	g_section_calls = 0;
	g_lc_calls = 0;
	g_segment_calls = 0;
	g_header_calls = 0;
	return EXIT_SUCCESS;
}

// static MunitResult	test_mach32_segment_addr(
// 	const MunitParameter params[], void *fixture) {
// 	t_ctx ctx;
// 	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
// 	t_dump_fxs funcs = { NULL, verify_segment_address, NULL, NULL	};

// 	(void)params;
// 	(void)fixture;
// 	bzero(&ctx, sizeof(t_ctx));
// 	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
// 	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
// 	munit_assert_int(dump_macho_bin(&ctx, &funcs), ==, EXIT_SUCCESS);
// 	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
// 		return MUNIT_ERROR;
// 	munit_assert_int(g_segment_calls, ==, 1);
// 	g_segment_calls = 0;
// 	return EXIT_SUCCESS;
// }

// static MunitResult	test_mach32_section_addr(
// 	const MunitParameter params[], void *fixture) {
// 	t_ctx ctx;
// 	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
// 	t_dump_fxs funcs = { NULL, NULL, verify_section_address, NULL	};

// 	(void)params;
// 	(void)fixture;
// 	bzero(&ctx, sizeof(t_ctx));
// 	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
// 	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
// 	munit_assert_int(dump_macho_bin(&ctx, &funcs), ==, EXIT_SUCCESS);
// 	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
// 		return MUNIT_ERROR;
// 	munit_assert_int(g_section_calls, ==, 1);
// 	g_section_calls = 0;
// 	return EXIT_SUCCESS;
// }

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_dump_fat_bin_dumps", test_dump_fat_bin_dumps, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
//  { "test_mach32_segment_addr", test_mach32_segment_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
//  { "test_mach32_section_addr", test_mach32_section_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_fat64_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/fat/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
