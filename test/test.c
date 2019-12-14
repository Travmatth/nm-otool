#include "tests.h"
#include <assert.h>
#include <mimick.h>

struct test_func	test_funcs[NUM_TESTS] = {
	{ "test_get_file_fails_dir", test_get_file_fails_dir },
	{ "test_get_file_opens_file", test_get_file_opens_file },
	{ "test_determine_file_detects_invalid", test_determine_file_detects_invalid },
	{ "test_determine_file_detects_macho64", test_determine_file_detects_macho64 },
	{ "test_determine_file_detects_macho32", test_determine_file_detects_macho32 },
	{ "test_determine_file_detects_archive", test_determine_file_detects_archive },
	{ "test_determine_file_detects_extended_archive", test_determine_file_detects_extended_archive, },
	{ "test_determine_file_detects_fat", test_determine_file_detects_fat },
	{ "test_dump_macho_bin_dumps_mach_32", test_dump_macho_bin_dumps_mach_32 },
	{ "test_mach32_segment_addr", test_mach32_segment_addr },
	{ "test_mach32_section_addr", test_mach32_section_addr },
	{ "test_format_pointer_makes_32bit_addr", test_format_pointer_makes_32bit_addr },
	{ "test_format_pointer_makes_64bit_addr", test_format_pointer_makes_64bit_addr },
	{ "test_format_mem_translates_1byte_mem", test_format_mem_translates_1byte_mem },
	{ "test_format_mem_translates_16byte_mem", test_format_mem_translates_16byte_mem },
	{ "test_print_text_segment", test_print_text_segment },
	{ "test_print_text_section", test_print_text_section },
	{ "test_print_text_segment_64", test_print_text_segment_64 },
	{ "test_print_text_section_64", test_print_text_section_64 },
};

/* Define the blueprint of a mock identified by `malloc_proto`
   that returns a `void *` and takes a `size_t` parameter. */
mmk_mock_define (malloc_mock, void *, size_t);

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	/***********************TEST********************************/
    /* Mock the malloc function in the current module using
       the `malloc_mock` blueprint. */
    mmk_mock("malloc@self", malloc_mock);

    /* Tell the mock to return NULL and set errno to ENOMEM
       whatever the given parameter is. */
    void *result = NULL;
    mmk_when(malloc(mmk_any(size_t)),
            .then_return = &result,
            .then_errno = ENOMEM);

    assert(malloc(42) == result && errno == ENOMEM);

    mmk_reset(malloc);
	/***********************TEST********************************/
	int j = NUM_TESTS; (void)j;
	for (int i = 0; i < NUM_TESTS; i++) {
		if (test_funcs[i].exec() == EXIT_FAILURE) {
			printf("Test failed: %s\n", test_funcs[i].name);
			return EXIT_FAILURE;
		}
		printf("Test passed: %s\n", test_funcs[i].name);
	}
	printf("Passed %d tests\n", NUM_TESTS);
	return EXIT_SUCCESS;
}
