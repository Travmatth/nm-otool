#ifndef TESTS_H
# define TESTS_H

#include "munit/munit.h"
#include "Mimick/include/mimick.h"
#include <string.h> // strcmp/bzero
#include "../includes/common.h"
#include "../includes/otool.h"

# define MACH_TESTS (3)
int		test_dump_macho_bin_dumps_mach_32(void);
int		test_mach32_segment_addr(void);
int		test_mach32_section_addr(void);

/*
tests
*/

# define NUM_TESTS (MACH_TESTS)

struct test_func {
	char	*name;
	int		(*exec)(void);
};

#endif
