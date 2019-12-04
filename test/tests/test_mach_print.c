#include "../tests.h"
#include <errno.h>

int		fd_to_str(int fd, char *out) {
	int bytes = 0;

	if ((bytes = read(fd, out, BUFSIZ)) == -1)
		return EXIT_FAILURE;
	out[bytes] = '\0';
	return EXIT_SUCCESS;
}

char *reference_segment_output = "test/artifacts/simple_program_32:\n\
Contents of (__TEXT,__text) section\n";

int		test_print_text_segment(void) {
	t_ctx ctx;
	int diff, orig = dup(STDOUT_FILENO), success, fds[2];
	char out[BUFSIZ], *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_fxs funcs = { NULL, print_text_segment, NULL, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (pipe(fds) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
		return EXIT_FAILURE;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// run func under test
	else if (dump_macho_bin(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	// evaluate test
	else if ((fd_to_str(fds[0], out) == EXIT_SUCCESS)
		&& !(diff = strcmp(reference_segment_output, out)))
		success = EXIT_SUCCESS;
	else
		success = EXIT_FAILURE;
	dup2(orig, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	return success;
}

char *reference_segment_output_64 = "test/artifacts/simple_program_64:\n\
Contents of (__TEXT,__text) section\n";

int		test_print_text_segment_64(void) {
	t_ctx ctx;
	int diff, orig = dup(STDOUT_FILENO), success, fds[2];
	char out[BUFSIZ], *argv[2] = { NULL, "test/artifacts/simple_program_64" };
	t_dump_fxs funcs = { NULL, print_text_segment, NULL, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (pipe(fds) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
		return EXIT_FAILURE;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// run func under test
	else if (dump_macho_bin64(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	// evaluate test
	else if ((fd_to_str(fds[0], out) == EXIT_SUCCESS)
		&& !(diff = strcmp(reference_segment_output_64, out)))
		success = EXIT_SUCCESS;
	else
		success = EXIT_FAILURE;
	dup2(orig, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	return success;
}

char *reference_section_output = "00001f00	55 89 e5 83 ec 18 e8 00 00 00 00 58 8b 4d 08 8d \n\
00001f10	80 8b 00 00 00 89 4d fc 8b 4d fc 89 04 24 89 4c \n\
00001f20	24 04 e8 51 00 00 00 89 45 f8 83 c4 18 5d c3 90 \n\
00001f30	55 89 e5 83 ec 08 8b 45 08 89 45 fc 8b 45 fc 89 \n\
00001f40	04 24 e8 b9 ff ff ff 83 c4 08 5d c3 0f 1f 40 00 \n\
00001f50	55 89 e5 83 ec 08 e8 00 00 00 00 58 8d 80 3e 00 \n\
00001f60	00 00 c7 45 fc 00 00 00 00 89 04 24 e8 bf ff ff \n\
00001f70	ff 31 c0 83 c4 08 5d c3 \n";

int		test_print_text_section(void) {
	t_ctx ctx;
	int diff, orig = dup(STDOUT_FILENO), success, fds[2];
	char out[BUFSIZ], *argv[2] = { NULL, "test/artifacts/simple_program_32" };
	t_dump_fxs funcs = { NULL, NULL, print_text_section, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (pipe(fds) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
		return EXIT_FAILURE;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// run func under test
	else if (dump_macho_bin(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	// evaluate test
	else if ((fd_to_str(fds[0], out) == EXIT_SUCCESS)
		&& !(diff = strcmp(reference_section_output, out)))
		success = EXIT_SUCCESS;
	else
		success = EXIT_FAILURE;
	dup2(orig, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	return success;
}

int		_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1 += 1;
		s2 += 1;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *reference_section_output_64 = "0000000100000f00	55 48 89 e5 48 83 ec 10 48 8d 05 87 00 00 00 48 \n\
0000000100000f10	89 7d f8 48 8b 75 f8 48 89 c7 b0 00 e8 53 00 00 \n\
0000000100000f20	00 89 45 f4 48 83 c4 10 5d c3 90 90 90 90 90 90 \n\
0000000100000f30	55 48 89 e5 48 83 ec 10 48 89 7d f8 48 8b 7d f8 \n\
0000000100000f40	e8 bb ff ff ff 48 83 c4 10 5d c3 0f 1f 44 00 00 \n\
0000000100000f50	55 48 89 e5 48 83 ec 10 48 8d 3d 3a 00 00 00 c7 \n\
0000000100000f60	45 fc 00 00 00 00 e8 c5 ff ff ff 31 c0 48 83 c4 \n\
0000000100000f70	10 5d c3 \n";

int		test_print_text_section_64(void) {
	t_ctx ctx;
	int diff, orig = dup(STDOUT_FILENO), success, fds[2];
	char out[BUFSIZ], *argv[2] = { NULL, "test/artifacts/simple_program_64" };
	t_dump_fxs funcs = { NULL, NULL, print_text_section, NULL };

	bzero(&ctx, sizeof(t_ctx));
	if (pipe(fds) == -1 || dup2(fds[1], STDOUT_FILENO) == -1)
		return EXIT_FAILURE;
	else if (get_file(2, argv, NULL, &ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// run func under test
	else if (dump_macho_bin64(&ctx, &funcs) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// close resources
	else if (cleanup_ctx(&ctx) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	// evaluate test
	else if ((fd_to_str(fds[0], out) == EXIT_SUCCESS)
		&& !(diff = strcmp(reference_section_output_64, out)))
		success = EXIT_SUCCESS;
	else
		success = EXIT_FAILURE;
	dup2(orig, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	return success;
}
