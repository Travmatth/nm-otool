#ifndef TESTS_H
# define TESTS_H

#include "munit/munit.h"
#include "Mimick/include/mimick.h"
#include <string.h> // strcmp/bzero
#include "../includes/common.h"
#include "../includes/otool.h"

/*
tests/test_mach_print.c
*/

# define MACH_PRINT_TESTS (4)
int		test_print_text_segment(void);
int		test_print_text_segment_64(void);
int		test_print_text_section(void);
int		test_print_text_section_64(void);

/*
tests/test_format.c
*/

# define FORMAT_TESTS (4)
int		test_format_pointer_makes_32bit_addr(void);
int		test_format_pointer_makes_64bit_addr(void);
int		test_format_mem_translates_16byte_mem(void);
int		test_format_mem_translates_1byte_mem(void);

/*
tests/test_utils.c
*/

# define UTILS_TESTS (8)
int		test_get_file_fails_dir(void);
int		test_get_file_opens_file(void);
int		test_determine_file_detects_invalid(void);
int		test_determine_file_detects_macho64(void);
int		test_determine_file_detects_macho32(void);
int		test_determine_file_detects_archive(void);
int		test_determine_file_detects_extended_archive(void);
int		test_determine_file_detects_fat(void);

/*
tests/test_utils.c
*/

# define MACH_TESTS (3)
int		test_dump_macho_bin_dumps_mach_32(void);
int		test_mach32_segment_addr(void);
int		test_mach32_section_addr(void);

/*
tests
*/

# define NUM_TESTS (MACH_PRINT_TESTS + FORMAT_TESTS + UTILS_TESTS + MACH_TESTS)

struct test_func {
	char	*name;
	int		(*exec)(void);
};

#endif
