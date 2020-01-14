#include "../tests.h"
#include <errno.h>

char *ref_i386_output = "test/artifacts/binary/main32:\n\
Contents of (__TEXT,__text) section\n\
00001e63	55 89 e5 53 83 ec 24 e8 df 00 00 00 c7 45 f4 01 \n\
00001e73	00 00 00 c7 45 f0 02 00 00 00 c7 45 ec 04 00 00 \n\
00001e83	00 c7 45 e8 08 00 00 00 c7 45 e4 07 00 00 00 8b \n\
00001e93	45 f4 0b 45 f0 83 ec 08 50 8d 83 ff 00 00 00 50 \n\
00001ea3	e8 aa 00 00 00 83 c4 10 8b 45 f4 0b 45 f0 0b 45 \n\
00001eb3	ec 83 ec 08 50 8d 83 09 01 00 00 50 e8 8e 00 00 \n\
00001ec3	00 83 c4 10 8b 45 f4 23 45 f0 83 ec 08 50 8d 83 \n\
00001ed3	17 01 00 00 50 e8 75 00 00 00 83 c4 10 8b 45 e4 \n\
00001ee3	23 45 f4 83 ec 08 50 8d 83 21 01 00 00 50 e8 5c \n\
00001ef3	00 00 00 83 c4 10 8b 45 e4 23 45 f0 83 ec 08 50 \n\
00001f03	8d 83 21 01 00 00 50 e8 43 00 00 00 83 c4 10 8b \n\
00001f13	45 e4 23 45 ec 83 ec 08 50 8d 83 21 01 00 00 50 \n\
00001f23	e8 2a 00 00 00 83 c4 10 8b 45 e4 23 45 e8 83 ec \n\
00001f33	08 50 8d 83 21 01 00 00 50 e8 11 00 00 00 83 c4 \n\
00001f43	10 b8 00 00 00 00 8b 5d fc c9 c3 8b 1c 24 c3 \n";

static MunitResult
test_print_i386_text_section(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	struct fixture s;
	char *out, *argv[2] = { NULL, "test/artifacts/binary/main32" };
	t_dump_fxs funcs = { NULL, NULL, print_i386_text_section, NULL, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (swap_stdout(&s) == EXIT_FAILURE)
		return MUNIT_ERROR;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return MUNIT_FAIL;
	else if (validate_file(ctx.file, &ctx, TRUE) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// run func under test
	else if (dump_mach_i386(ctx.file, &ctx, &funcs) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	// evaluate test
	int status = fd_to_str(s.stdout_fds[0], &out);
	if (restore_stdout(&s) == EXIT_FAILURE || status == EXIT_FAILURE)
		return MUNIT_ERROR;
	munit_assert_string_equal(ref_i386_output, out);
	return MUNIT_OK;
}

static MunitResult
test_print_swapped_i386_text_section(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	struct fixture s;
	char *out, *argv[2] = { NULL, "test/artifacts/binary/ppc_only" };
	t_dump_fxs funcs = { NULL, NULL, print_i386_text_section, NULL, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (swap_stdout(&s) == EXIT_FAILURE)
		return MUNIT_ERROR;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// run func under test
	else if (file_multiplexer(ctx.file, &ctx, &funcs, TRUE) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	// evaluate test
	struct stat buf;
	int b = open("test/tests/swapped_ref.txt", O_RDONLY);
	fstat(b, &buf);
	char *ref_swapped_i386_output = mmap(NULL, buf.st_size, MMAP_PROT, MMAP_FLAGS, b, 0);
	int status = fd_to_str(s.stdout_fds[0], &out);
	if (restore_stdout(&s) == EXIT_FAILURE || status == EXIT_FAILURE)
		return MUNIT_ERROR;
	munit_assert_string_equal(ref_swapped_i386_output, out);
	return MUNIT_OK;
}

char *ref_x86_64_output = "test/artifacts/binary/a.out:\n\
Contents of (__TEXT,__text) section\n\
0000000100000f50	55 48 89 e5 48 83 ec 10 bf 01 00 00 00 48 8d 35 \n\
0000000100000f60	42 00 00 00 b8 0c 00 00 00 89 c2 c7 45 fc 00 00 \n\
0000000100000f70	00 00 e8 0f 00 00 00 31 ff 48 89 45 f0 89 f8 48 \n\
0000000100000f80	83 c4 10 5d c3 \n";

static MunitResult
test_print_x86_64_text_section(
	MUNIT_UNUSED const MunitParameter params[], MUNIT_UNUSED void *fixture) {
	t_ctx ctx;
	struct fixture s;
	char *out, *argv[2] = { NULL, "test/artifacts/binary/a.out" };
	t_dump_fxs funcs = { NULL, NULL, NULL, print_x86_64_text_section, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (swap_stdout(&s) == EXIT_FAILURE)
		return MUNIT_ERROR;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return MUNIT_FAIL;
	else if (validate_file(ctx.file, &ctx, TRUE) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// run func under test
	else if (dump_mach_x86_64(ctx.file, &ctx, &funcs) == EXIT_FAILURE)
		return MUNIT_FAIL;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return MUNIT_FAIL;
	// evaluate test
	int status = fd_to_str(s.stdout_fds[0], &out);
	if (restore_stdout(&s) == EXIT_FAILURE || status == EXIT_FAILURE)
		return MUNIT_ERROR;
	munit_assert_string_equal(ref_x86_64_output, out);
	return MUNIT_OK;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_print_i386_text_section", test_print_i386_text_section, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_print_swapped_i386_text_section", test_print_swapped_i386_text_section, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_print_x86_64_text_section", test_print_x86_64_text_section, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite mach_print_suite = {
	//{ name, tests, suites, iterations, options },
    "/mach/print/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
