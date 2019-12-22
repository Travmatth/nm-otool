#include "../tests.h"

static MunitResult
test_get_file_fails_dir(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/" };
	int orig = dup(STDOUT_FILENO);

	bzero(&ctx, sizeof(t_ctx));
	close(STDERR_FILENO);
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_FAILURE);
	dup2(orig, STDERR_FILENO);
	return MUNIT_OK;
}

static MunitResult
test_get_file_opens_file(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char ref[83] = {0}, *argv[2] = { NULL, "test/artifacts/README.md" };

	int fd = open(argv[1], O_RDONLY);
	read(fd, ref, 82);
	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_string_equal(ctx.file, ref);
	munit_assert_size(ctx.size, ==, 82);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_invalid(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/README.md" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_FAILURE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_corrupt_magic(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/fat/fat_corr7" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_FAILURE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_fat(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/fat/fat" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_FAT);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_i386(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/binary/main32" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(!(ctx.flags & IS_FAT) && (ctx.flags & IS_32));
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_x86_64(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/binary/a.out" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_false((ctx.flags & IS_FAT) || (ctx.flags & IS_32));
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_archive(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/archive/_lft.a" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_ARCHIVE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitResult
test_determine_file_detects_extended_archive(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/archive/test.a" };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(ctx.flags & IS_EXTENDED_ARCHIVE);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_ERROR;
	return MUNIT_OK;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
{ "test_get_file_fails_dir", test_get_file_fails_dir, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_get_file_opens_file", test_get_file_opens_file, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_invalid", test_determine_file_detects_invalid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_corrupt_magic", test_determine_file_detects_corrupt_magic, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_fat", test_determine_file_detects_fat, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_i386", test_determine_file_detects_i386, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_x86_64", test_determine_file_detects_x86_64, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_archive", test_determine_file_detects_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_extended_archive", test_determine_file_detects_extended_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
/* Mark the end of the array with an entry where the test function is NULL */
{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_utils_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/utils/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
