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
int		test_determine_file_detects_fat32(void);
int		test_swap_32bit(void);
int		test_swap_64bit(void);
#endif
