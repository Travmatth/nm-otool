#include "../tests.h"
#include <inttypes.h>

static int	g_header_calls = 0;
static int	g_segment_calls = 0;
static int	g_lc_calls = 0;
static int	g_section_calls = 0;

/*
	verify dumping header, load commands, segments and sections of a mach-o 32 bit binary
*/

int		verify_header(t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)ctx;
	(void)header_64;
	if (header) {
		if (header->magic == MH_MAGIC)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_segments(t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64, void *addr) {
	(void)ctx;
	(void)segment;
	(void)segment_64;
	(void)addr;
	g_segment_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_load_command(t_ctx *ctx, struct load_command *lc, void *addr) {
	(void)ctx;
	(void)lc;
	(void)addr;
	g_lc_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_sections(t_ctx *ctx, struct section *sect, struct section_64 *sect64, void *addr) {
	(void)ctx;
	(void)sect;
	(void)sect64;
	(void)addr;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

int		test_dump_macho_bin_dumps_mach_32(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = {
		verify_header,
		verify_segments,
		verify_sections,
		verify_load_command
	};

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_macho_bin(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	else if (g_header_calls != 1)
		return EXIT_FAILURE;
	else if (g_segment_calls != 4)
		return EXIT_FAILURE;
	else if (g_lc_calls != 11)
		return EXIT_FAILURE;
	else if (g_section_calls != 7)
		return EXIT_FAILURE;
	g_section_calls = 0;
	g_lc_calls = 0;
	g_segment_calls = 0;
	g_header_calls = 0;
	return EXIT_SUCCESS;
}

/*
	verify segment address of mach-o 32 bit binary is correct
*/

int		verify_segment_address(t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64, void *addr) {
	(void)ctx;
	(void)segment_64;
	if (!strcmp(segment->segname, "__TEXT")) {
		uint32_t magic = *(uint32_t *)addr;
		if (magic == MH_MAGIC)
			g_segment_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		test_mach32_segment_addr(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = { NULL, verify_segment_address, NULL, NULL	};

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_macho_bin(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	else if (g_segment_calls != 1)
		return EXIT_FAILURE;
	g_segment_calls = 0;
	return EXIT_SUCCESS;
}

/*
	verify section address of mach-o 32 bit binary is correct
*/

int		verify_section_address(t_ctx *ctx, struct section *sect, struct section_64 *sect64, void *addr) {
	(void)ctx;
	(void)sect;
	(void)sect64;
	(void)addr;
	if (!strcmp("__text", sect->sectname)) {
		uint64_t val = *(uint64_t*)addr;
		if (val == 0xE818EC83E58955ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		test_mach32_section_addr(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = { NULL, NULL, verify_section_address, NULL	};

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_macho_bin(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	else if (g_section_calls != 1)
		return EXIT_FAILURE;
	g_section_calls = 0;
	return EXIT_SUCCESS;
}
