#include "../tests.h"

int		test_format_pointer_makes_32bit_addr(void) {
	char		ptr_buf[17] = {'1'};
	uint32_t	offset = 7936;

	format_pointer(offset, ptr_buf, FALSE);
	if (strcmp("00001f00", ptr_buf))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		test_format_pointer_makes_64bit_addr(void) {
	char		ptr_buf[17] = {'1'};
	uint64_t	offset = 4294971136;

	format_pointer(offset, ptr_buf, TRUE);
	if (strcmp("0000000100000f00", ptr_buf))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		test_format_mem_translates_1byte_mem(void) {
	uint64_t 	val = 0x00E818EC83E58955ULL;
	char		mem_buf[49] = {'1'};
	uint64_t	current = 0;

	format_mem((void*)&val, &current, 1, mem_buf);
	if (strcmp("55 ", mem_buf) || current != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		test_format_mem_translates_16byte_mem(void) {
	uint64_t 	val[2] = { 0x00E818EC83E58955ULL, 0x8d084d8b58000000ULL };
	char		mem_buf[49] = {'1'};
	uint64_t	current = 0;

	format_mem((void*)&val, &current, sizeof(uint64_t) * 2, mem_buf);
	if (strcmp("55 89 e5 83 ec 18 e8 00 00 00 00 58 8b 4d 08 8d ", mem_buf) || current != 16)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}