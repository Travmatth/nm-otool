#include "tests.h"

struct func {
	char	*name;
	int		(*exec)(void);
};

# define NUM_TESTS (UTILS_TESTS)

struct func		funcs[NUM_TESTS] = {
	{ "test_get_file_fails_dir", test_get_file_fails_dir },
	{ "test_get_file_opens_file", test_get_file_opens_file },
	{ "test_determine_file_detects_invalid", test_determine_file_detects_invalid },
	{ "test_determine_file_detects_macho64", test_determine_file_detects_macho64 },
	{ "test_determine_file_detects_macho32", test_determine_file_detects_macho32 },
	{ "test_determine_file_detects_fat32", test_determine_file_detects_fat32 },
	{ "test_swap_32bit", test_swap_32bit },
	{ "test_swap_64bit", test_swap_64bit },
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
	printf("Passed %d tests\n", NUM_TESTS);
	return EXIT_SUCCESS;
}
