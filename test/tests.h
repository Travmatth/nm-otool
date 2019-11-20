#ifndef TESTS_H
# define TESTS_H

#include <string.h> // strcmp/bzero
#include "../includes/common.h"

/*
tests/test_utils.c
*/

# define UTILS_TESTS (10)
int		test_get_file_fails_dir(void);
int		test_get_file_opens_file(void);
int		test_determine_file_detects_invalid(void);
int		test_determine_file_detects_macho64(void);
int		test_determine_file_detects_macho32(void);
int		test_determine_file_detects_archive(void);
int		test_determine_file_detects_extended_archive(void);
int		test_determine_file_detects_fat(void);
#endif
