#include "../tests.h"

/*
should detect and fail to open dir passed as arg
*/

int		test_get_file_fails_dir(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/" };
	int orig = dup(STDOUT_FILENO);

	close(STDERR_FILENO);
	if (get_file(2, argv, NULL, &ctx) == EXIT_SUCCESS)
		return EXIT_FAILURE;
	dup2(orig, STDERR_FILENO);
	return EXIT_SUCCESS;
}

/*
should open valid filename into mmapped pointer
*/

int		test_get_file_opens_file(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/text.txt" };

	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (strcmp(ctx.file, "test"))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
