#include <string.h> // strcmp
#include "../includes/common.h"

struct func {
	char	*name;
	int		(*exec)(void);
};

/*
should detect and fail to open dir passed as arg
*/

int		test_get_file_fails_dir(void) {
	char *file, *argv[2] = { NULL, "test/" };
	int orig = dup(STDOUT_FILENO);

	close(STDERR_FILENO);
	if (get_file(2, argv, NULL, &file) == EXIT_SUCCESS)
		return EXIT_FAILURE;
	dup2(orig, STDERR_FILENO);
	return EXIT_SUCCESS;
}

/*
should open valid filename into mmapped pointer
*/

int		test_get_file_opens_file(void) {
	char *file, *argv[2] = { NULL, "test/artifacts/text.txt" };

	if (get_file(2, argv, NULL, &file) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (strcmp(file, "test"))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

# define NUM_TESTS 2
struct func		funcs[NUM_TESTS] = {
	{ "test_get_file_opens_file", test_get_file_opens_file },
	{ "test_get_file_fails_dir", test_get_file_fails_dir },
};

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	for (int i = 0; i < NUM_TESTS; i++) {
		if (funcs[i].exec() == EXIT_FAILURE) {
			printf("Test failed: %s\n", funcs[i].name);
			return EXIT_FAILURE;
		}
		printf("Test passed: %s\n", funcs[i].name);
	}
	return EXIT_SUCCESS;
}
