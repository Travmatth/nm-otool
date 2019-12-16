#include "../tests.h"

static MunitResult	test_get_file_fails_dir(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/" };
	int orig = dup(STDOUT_FILENO);

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	close(STDERR_FILENO);
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_FAILURE);
	dup2(orig, STDERR_FILENO);
	return MUNIT_OK;
}

static MunitResult	test_get_file_opens_file(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/text.txt" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_string_equal(ctx.file, "test");
	munit_assert_size(ctx.size, ==, 4);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_invalid(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/text.txt" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_FAILURE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_macho64(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_64" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_false((ctx.flags & IS_FAT) || (ctx.flags & IS_32));
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_macho32(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(!(ctx.flags & IS_FAT) && (ctx.flags & IS_32));
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_archive(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/archive_mixed_not_lib.a" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_ARCHIVE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_extended_archive(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/extended_archive_multi_lib.a" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_EXTENDED_ARCHIVE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult	test_determine_file_detects_fat(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_obj_fat.o" };

	(void)params;
	(void)fixture;
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_FAT);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_get_file_fails_dir", test_get_file_fails_dir, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_get_file_opens_file", test_get_file_opens_file, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_invalid", test_determine_file_detects_invalid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_macho64", test_determine_file_detects_macho64, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_macho32", test_determine_file_detects_macho32, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_archive", test_determine_file_detects_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_extended_archive", test_determine_file_detects_extended_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_determine_file_detects_fat", test_determine_file_detects_fat, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_utils_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/utils/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
