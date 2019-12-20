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

extern char* fat_file_params[];

static MunitParameterEnum detect_fat_params[] = {
  { "fat_file", fat_file_params },
  { NULL, NULL },
};

static void
*detect_fat_file_test_setup(
	const MunitParameter params[], MUNIT_UNUSED void *user_data) {
	int	*status = (int*)malloc(sizeof(int));
	if (strcmp("test/artifacts/fat/fat_corr7", params->value))
		*status = EXIT_SUCCESS;
	else
		*status = EXIT_FAILURE;
	return (void*)status;
}

static void
detect_fat_file_test_teardown(void *user_data) {
  free(user_data);
}

static MunitResult
test_determine_file_detects_fat(
	const MunitParameter params[], void *fixture) {
	t_ctx ctx;
	int	result = *(int*)fixture;
	char *argv[2] = { NULL, params->value };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, result);
	if (result == EXIT_SUCCESS)
		munit_assert_true(ctx.flags & IS_FAT);
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

extern char* i386_file_params[];

static MunitParameterEnum detect_i386_params[] = {
  { "i386_file", i386_file_params },
  { NULL, NULL },
};

static MunitResult
test_determine_file_detects_i386(
	const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, params->value };

	bzero(&ctx, sizeof(t_ctx));
	munit_assert_int(get_file(2, argv, NULL, &ctx), ==, EXIT_SUCCESS);
	munit_assert_int(determine_file(&ctx), ==, EXIT_SUCCESS);
	munit_assert_true(!(ctx.flags & IS_FAT) && (ctx.flags & IS_32));
	if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	return MUNIT_OK;
}

extern char* x86_64_file_params[];

static MunitParameterEnum detect_x86_64_params[] = {
  { "x86_64_file", x86_64_file_params },
  { NULL, NULL },
};

static MunitResult
test_determine_file_detects_x86_64(
	const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	char *argv[2] = { NULL, params->value };

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
	char *argv[2] = { NULL, "test/artifacts/archive_mixed_not_lib.a" };

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
	char *argv[2] = { NULL, "test/artifacts/extended_archive_multi_lib.a" };

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
{ "test_determine_file_detects_fat", test_determine_file_detects_fat, detect_fat_file_test_setup, detect_fat_file_test_teardown, MUNIT_TEST_OPTION_NONE, detect_fat_params },
{ "test_determine_file_detects_i386", test_determine_file_detects_i386, NULL, NULL, MUNIT_TEST_OPTION_NONE, detect_i386_params },
{ "test_determine_file_detects_x86_64", test_determine_file_detects_x86_64, NULL, NULL, MUNIT_TEST_OPTION_NONE, detect_x86_64_params },
{ "test_determine_file_detects_archive", test_determine_file_detects_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
{ "test_determine_file_detects_extended_archive", test_determine_file_detects_extended_archive, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
/* Mark the end of the array with an entry where the test function is NULL */
{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_utils_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/utils/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
