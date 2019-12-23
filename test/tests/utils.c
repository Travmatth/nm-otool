#include "../tests.h"

/*
** Mock callbacks to test various functions
*/

int	g_header_calls = 0;
int	g_segment_calls = 0;
int	g_lc_calls = 0;
int	g_section_calls = 0;

int		verify_segments(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
	(void)file;
	(void)ctx;
	(void)segment;
	(void)segment_64;
	g_segment_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_load_command(char *file, t_ctx *ctx, struct load_command *lc, void *addr) {
	(void)file;
	(void)ctx;
	(void)lc;
	(void)addr;
	g_lc_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_sections(char *file, t_ctx *ctx, struct section *section, struct section_64 *section_64) {
	(void)file;
	(void)ctx;
	(void)section;
	(void)section_64;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_segment_address(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64) {
	(void)ctx;
	(void)segment_64;
	if (!strcmp(segment->segname, "__TEXT")) {
		uint32_t magic = *(uint32_t *)file + segment->fileoff;
		if (magic == MH_MAGIC)
			g_segment_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64) {
	(void)ctx;
	(void)sect64;
	if (!strcmp("__text", sect->sectname)) {
		uint64_t val = *(uint64_t*)(file + sect->offset);
		if (val == 0xe824ec8353e58955ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_header(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)file;
	(void)ctx;
	(void)header_64;
	if (header) {
		if (header->magic == MH_MAGIC)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section64_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64) {
	(void)ctx;
	(void)sect;
	if (!strcmp("__text", sect64->sectname)) {
		uint64_t val = *(uint64_t*)(file + sect64->offset);
		if (val == 1219493948222425173ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_header64(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64) {
	(void)file;
	(void)ctx;
	(void)header;
	if (header_64) {
		if (header_64->magic == MH_MAGIC_64)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

/*
** test utils
*/

int		fd_to_str(int fd, char *out) {
	int bytes = 0;

	if ((bytes = read(fd, out, BUFSIZ)) == -1)
		return EXIT_FAILURE;
	out[bytes] = '\0';
	return EXIT_SUCCESS;
}

int		swap_stdout(struct fixture *s) {
	s->stdout = dup(STDOUT_FILENO);
	if (pipe(s->fds) == -1)
		return EXIT_FAILURE;
	if (dup2(s->fds[1], STDOUT_FILENO) == -1)
		return MUNIT_ERROR;
	return EXIT_SUCCESS;
}

int		restore_stdout(struct fixture *s) {
	if (dup2(s->stdout, STDOUT_FILENO) == -1
		|| close(s->fds[0]) == -1
		|| close(s->fds[1]) == -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
