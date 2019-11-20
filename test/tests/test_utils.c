#include "../tests.h"

/*
should detect and fail to open dir passed as arg
*/

int		test_get_file_fails_dir(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/" };
	int orig = dup(STDOUT_FILENO);

	bzero(&ctx, sizeof(t_ctx));
	close(STDERR_FILENO);
	int status = get_file(2, argv, NULL, &ctx);
	dup2(orig, STDERR_FILENO);
	if (status == EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should open valid filename into mmapped pointer
*/

int		test_get_file_opens_file(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/text.txt" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (strcmp(ctx.file, "test"))
		return EXIT_FAILURE;
	else if (ctx.size != 4)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file not mach-o or fat formatted
*/

int		test_determine_file_detects_invalid(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/text.txt" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_SUCCESS)
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file mach-o 64 bit binary
*/

int		test_determine_file_detects_macho64(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || (ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file mach-o 32 bit binary
*/

int		test_determine_file_detects_macho32(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_program_32" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if ((ctx.flags & IS_FAT) || !(ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file fat 64 bit binary
*/

int		test_determine_file_detects_fat32(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_lib_fat.a" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (!(ctx.flags & IS_FAT))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
test reversing 32bit number
*/

int		test_swap_32bit(void) {
	uint32_t orig = swap_uint32(MH_MAGIC);
	if (orig != MH_CIGAM)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
test reversing 64bit number
*/

int		test_swap_64bit(void) {
	uint64_t orig = swap_uint64(MH_MAGIC_64);
	if (orig != OSSwapConstInt64(MH_MAGIC_64))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
