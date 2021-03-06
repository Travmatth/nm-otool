#include "../tests.h"

static void*
test_setup(const MunitParameter params[], MUNIT_UNUSED void *data) {
	int	val;
	pid_t ret, pid;
	struct fixture *s = malloc(sizeof(struct fixture));

	swap_stdout(s);
	swap_stderr(s);
	if ((pid = fork()) == -1) {
		return NULL;
	} else if (pid == 0) { // child
		execlp("otool", "otool", "-t", params->value, NULL);
		printf("Execlp Error");
		_exit(EXIT_FAILURE);
	}
	while ((ret = waitpid(pid, &val, WNOHANG)) != pid) {}
	if (WIFEXITED(val))
		s->exit_status = WEXITSTATUS(val);
	int valid __attribute__((unused)) = fcntl(STDERR_FILENO, F_GETFD);
	if (s->exit_status == EXIT_SUCCESS &&
		fd_to_str(s->stdout_fds[0], &s->otool_output) == EXIT_FAILURE)
		return NULL;
	return (void*)s;
}

static void
test_teardown(void *fixture) {
	restore_stdout((struct fixture*)fixture);
	restore_stderr((struct fixture*)fixture);
	free(fixture);
}

extern char	*binary_file_params[];

static MunitParameterEnum binary_params[] = {
	{"file", binary_file_params},
	{NULL, NULL},
};

static MunitResult
test_otool_main_binary_files(
	const MunitParameter params[], void *fix) {
	struct fixture *fixture = (struct fixture *)fix;
	char *out, *argv[2] = { "./ft_otool", params->value };

	int status = otool_main(2, argv, NULL);
	if (strcmp(params->value, "test/artifacts/binary/corr1"))
		munit_assert_int(fixture->exit_status, ==, status);
	if (fixture->exit_status == EXIT_SUCCESS
		&& strcmp(params->value, "test/artifacts/binary/ls_reversed_magic")
		&& strcmp(params->value, "test/artifacts/binary/corr1")
		&& strcmp(params->value, "test/artifacts/binary/test_de_la_muerte")) {
		if (fd_to_str(fixture->stdout_fds[0], &out))
			return MUNIT_ERROR;
		munit_assert_string_equal(fixture->otool_output, out);
	}
	return MUNIT_OK;
}

extern char	*fat_file_params[];

static MunitParameterEnum fat_params[] = {
	{"file", fat_file_params},
	{NULL, NULL},
};

static MunitResult
test_otool_main_fat_files(
	const MunitParameter params[], void *fix) {
	struct fixture *fixture = (struct fixture *)fix;
	char *out, *argv[2] = { "./ft_otool", params->value };

	int status = otool_main(2, argv, NULL);
	munit_assert_int(fixture->exit_status, ==, status);
	if (fixture->exit_status == EXIT_SUCCESS) {
		if (fd_to_str(fixture->stdout_fds[0], &out))
			return MUNIT_ERROR;
		munit_assert_string_equal(fixture->otool_output, out);
	}
	return MUNIT_OK;
}

extern char	*object_file_params[];

static MunitParameterEnum object_params[] = {
	{"file", object_file_params},
	{NULL, NULL},
};

static MunitResult
test_otool_main_object_files(
	const MunitParameter params[], void *fix) {
	struct fixture *fixture = (struct fixture *)fix;
	char *out, *argv[2] = { "./ft_otool", params->value };

	int status = otool_main(2, argv, NULL);
	munit_assert_int(fixture->exit_status, ==, status);
	if (fixture->exit_status == EXIT_SUCCESS) {
		if (fd_to_str(fixture->stdout_fds[0], &out))
			return MUNIT_ERROR;
		munit_assert_string_equal(fixture->otool_output, out);
	}
	return MUNIT_OK;
}

extern char	*lib_file_params[];

static MunitParameterEnum lib_params[] = {
	{"file", lib_file_params},
	{NULL, NULL},
};

static MunitResult
test_otool_main_lib_files(
	const MunitParameter params[], void *fix) {
	struct fixture *fixture = (struct fixture *)fix;
	char *out, *argv[2] = { "./ft_otool", params->value };

	int status = otool_main(2, argv, NULL);
	if (strcmp(params->value, "test/artifacts/lib/lib_archive_medium"))
		munit_assert_int(fixture->exit_status, ==, status);
	if (fixture->exit_status == EXIT_SUCCESS &&
		strcmp(params->value, "test/artifacts/lib/lib_archive_medium")) {
		if (fd_to_str(fixture->stdout_fds[0], &out))
			return MUNIT_ERROR;
		munit_assert_string_equal(fixture->otool_output, out);
	}
	return MUNIT_OK;
}

extern char	*archive_file_params[];

static MunitParameterEnum archive_params[] = {
	{"file", archive_file_params},
	{NULL, NULL},
};

static MunitResult
test_otool_main_archive_files(
	const MunitParameter params[], void *fix) {
	struct fixture *fixture = (struct fixture *)fix;
	char *out, *argv[2] = { "./ft_otool", params->value };

	int status = otool_main(2, argv, NULL);
	munit_assert_int(fixture->exit_status, ==, status);
	if (fixture->exit_status == EXIT_SUCCESS) {
		if (fd_to_str(fixture->stdout_fds[0], &out))
			return MUNIT_ERROR;
		munit_assert_string_equal(fixture->otool_output, out);
	}
	return MUNIT_OK;
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_otool_main_archive_files", test_otool_main_archive_files, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, archive_params },
 { "test_otool_main_binary_files", test_otool_main_binary_files, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, binary_params },
 { "test_otool_main_fat_files", test_otool_main_fat_files, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, fat_params },
 { "test_otool_main_object_files", test_otool_main_object_files, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, object_params },
 { "test_otool_main_lib_files", test_otool_main_lib_files, test_setup, test_teardown, MUNIT_TEST_OPTION_NONE, lib_params },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite otool_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/macho/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
