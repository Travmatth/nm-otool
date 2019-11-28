#include "tests.h"

struct func {
	char	*name;
	int		(*exec)(void);
};

struct func		funcs[NUM_TESTS] = {
	{ "test_get_file_fails_dir", test_get_file_fails_dir },
	{ "test_get_file_opens_file", test_get_file_opens_file },
	{ "test_determine_file_detects_invalid", test_determine_file_detects_invalid },
	{ "test_determine_file_detects_macho64", test_determine_file_detects_macho64 },
	{ "test_determine_file_detects_macho32", test_determine_file_detects_macho32 },
	{ "test_determine_file_detects_archive", test_determine_file_detects_archive },
	{ "test_determine_file_detects_extended_archive", test_determine_file_detects_extended_archive, },
	{ "test_determine_file_detects_fat", test_determine_file_detects_fat },
	{ "test_dump_mach_lcmds_iters_all_segments", test_dump_mach_lcmds_iters_all_segments },
	{ "test_dump_mach_lcmds_iters_all_load_commands", test_dump_mach_lcmds_iters_all_load_commands },
	{ "test_dump_mach_lcmds_iters_all_segment_sections", test_dump_mach_lcmds_iters_all_segment_sections},
};

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	int j = NUM_TESTS; (void)j;
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
