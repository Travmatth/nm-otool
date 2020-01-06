#include "../tests.h"

static MunitResult
test_format_pointer_makes_32bit_addr(
	MUNIT_UNUSED const MunitParameter params[],
	MUNIT_UNUSED void* fixture) {
	char		ptr_buf[17] = {'1'};
	uint32_t	offset = 7936;

	format_pointer(offset, ptr_buf, FALSE);
	munit_assert_string_equal("00001f00", ptr_buf);
	return (MUNIT_OK);
}

static MunitResult
test_format_pointer_makes_64bit_addr(
	MUNIT_UNUSED const MunitParameter params[],
	MUNIT_UNUSED void *fixture) {
	char		ptr_buf[17] = {'1'};
	uint64_t	offset = 4294971136;

	format_pointer(offset, ptr_buf, TRUE);
	munit_assert_string_equal("0000000100000f00", ptr_buf);
	return (MUNIT_OK);
}

static MunitResult
test_format_mem_translates_1byte_mem(
	MUNIT_UNUSED const MunitParameter params[],
	MUNIT_UNUSED void *fixture) {
	uint64_t 	val = 0x00E818EC83E58955ULL;
	char		mem_buf[49] = {'1'};
	uint64_t	current = 0;

	format_mem((void*)&val, &current, 1, mem_buf);
	munit_assert_string_equal("55", mem_buf);
	return (MUNIT_OK);
}

static MunitResult
test_format_mem_translates_16byte_mem(
	MUNIT_UNUSED const MunitParameter params[],
	MUNIT_UNUSED void *fixture) {
	uint64_t 	val[2] = { 0x00E818EC83E58955ULL, 0x8d084d8b58000000ULL };
	char		*mem = "5589e583ec18e800000000588b4d088d";
	char		mem_buf[49] = {'1'};
	uint64_t	current = 0;

	format_mem((void*)&val, &current, sizeof(uint64_t) * 2, mem_buf);
	munit_assert_string_equal(mem, mem_buf);
	munit_assert_uint64(current, ==, 16);
	return (MUNIT_OK);
}

static MunitTest tests[] = {
//{ name , test , setup , tear_down , options, parameters },
 { "test_format_pointer_makes_32bit_addr", test_format_pointer_makes_32bit_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_format_pointer_makes_64bit_addr", test_format_pointer_makes_64bit_addr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_format_mem_translates_1byte_mem", test_format_mem_translates_1byte_mem, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 { "test_format_mem_translates_16byte_mem", test_format_mem_translates_16byte_mem, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
 /* Mark the end of the array with an entry where the test function is NULL */
 { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite common_format_suite = {
	//{ name, tests, suites, iterations, options },
    "/common/format/", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
