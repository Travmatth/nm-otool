#include "../tests.h"

static int	g_calls = 0;
static int	g_lc_calls = 0;
static int	g_section_calls = 0;

int		verify_segments(t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64, void *addr) {
	(void)ctx;
	(void)segment;
	(void)segment_64;
	(void)addr;
	g_calls += 1;
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

/*
iterate over all segments
*/
int		test_dump_mach_lcmds_iters_all_segments(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = { verify_segments, NULL, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_mach_lcmds(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (g_calls != 4)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	g_calls = 0;
	return EXIT_SUCCESS;
}

/*
iterate over all load commands
*/
int		test_dump_mach_lcmds_iters_all_load_commands(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = { verify_segments, NULL, verify_load_command };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_mach_lcmds(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (g_calls != 4 || g_lc_calls != 11)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	g_calls = 0;
	g_lc_calls = 0;
	return EXIT_SUCCESS;
}

/*
iterate over all sections of a segment
*/
int		test_dump_mach_lcmds_iters_all_segment_sections(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_funcs funcs = { NULL, verify_sections, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (dump_mach_lcmds(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (g_section_calls != 7)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	g_section_calls = 0;
	return EXIT_SUCCESS;
}
