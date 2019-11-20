#ifndef TESTS_H
# define TESTS_H

#include <string.h> // strcmp
#include "../includes/common.h"

/*
tests/test_utils.c
*/

# define UTILS_TESTS (2)
int		test_get_file_fails_dir(void);
int		test_get_file_opens_file(void);
#endif
