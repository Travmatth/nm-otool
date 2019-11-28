#ifndef TESTS_H
# define TESTS_H

#include <string.h> // strcmp/bzero
#include "../includes/common.h"

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
int		test_dump_mach_lcmds_iters_all_segments(void);
int		test_dump_mach_lcmds_iters_all_load_commands(void);
int		test_dump_mach_lcmds_iters_all_segment_sections(void);

# define NUM_TESTS (UTILS_TESTS + MACH_TESTS)
#endif
