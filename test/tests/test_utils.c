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
	char *argv[2] = { NULL, "test/artifacts/simple_program_64" };

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
should determine if given file standard archive
*/

int		test_determine_file_detects_archive(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/archive_mixed_not_lib.a" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (!(ctx.flags & IS_ARCHIVE))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file standard archive
*/

int		test_determine_file_detects_extended_archive(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/extended_archive_multi_lib.a" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (!(ctx.flags & IS_EXTENDED_ARCHIVE))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*
should determine if given file fat bit binary
*/

int		test_determine_file_detects_fat(void) {
	t_ctx ctx;
	char *argv[2] = { NULL, "test/artifacts/simple_obj_fat.o" };

	bzero(&ctx, sizeof(t_ctx));
	if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (!(ctx.flags & IS_FAT) || (ctx.flags & IS_32))
		return EXIT_FAILURE;
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
