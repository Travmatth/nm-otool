#include "../tests.h"

/*
** Mock callbacks to test various functions
*/

int	g_header_calls = 0;
int	g_segment_calls = 0;
int	g_lc_calls = 0;
int	g_section_calls = 0;

int		verify_i386_segments(char *file, t_ctx *ctx, int flags, struct segment_command *segment) {
	(void)file;
	(void)ctx;
	(void)flags;
	(void)segment;
	g_segment_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_x86_64_segments(char *file, t_ctx *ctx, int flags, struct segment_command_64 *segment_64) {
	(void)file;
	(void)ctx;
	(void)flags;
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

int		verify_i386_sections(struct section *sect, t_ctx *ctx, int flags) {
	(void)sect;
	(void)ctx;
	(void)flags;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_x86_64_sections(struct section_64 *sect, t_ctx *ctx, int flags) {
	(void)sect;
	(void)ctx;
	(void)flags;
	g_section_calls += 1;
	return EXIT_SUCCESS;
}

int		verify_i386_segment_address(struct segment_command *segment, t_ctx *ctx, int flags) {
	(void)ctx;
	(void)flags;
	if (!strcmp(segment->segname, SEG_TEXT)) {
		uint32_t magic = *(uint32_t *)ctx->file + segment->fileoff;
		if (magic == MH_MAGIC)
			g_segment_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_x86_64_segment_address(struct segment_command_64 *segment, t_ctx *ctx, int flags) {
	(void)ctx;
	(void)flags;
	if (!strcmp(segment->segname, SEG_TEXT)) {
		uint32_t magic = *(uint32_t *)ctx->file + segment->fileoff;
		if (magic == MH_MAGIC)
			g_segment_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section_i386_address(struct section *sect, t_ctx *ctx, int flags) {
	(void)flags;
	if (!strcmp(SECT_TEXT, sect->sectname)) {
		uint64_t val = *(uint64_t*)(ctx->file + sect->offset);
		if (val == 0xe824ec8353e58955ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_section_x86_64_address(struct section_64 *sect, t_ctx *ctx, int flags) {
	(void)flags;
	if (!strcmp(SECT_TEXT->sectname)) {
		uint64_t val = *(uint64_t*)(ctx->file + sect->offset);
		if (val == 0xe824ec8353e58955ULL)
			g_section_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_i386_header(struct mach_header *header, t_ctx *ctx, int flags) {
	(void)ctx;
	(void)flags;
	if (header) {
		if (header->magic == MH_MAGIC)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

int		verify_x86_64_header(struct mach_header_64 *header, t_ctx *ctx, int flags) {
	(void)ctx;
	(void)flags;
	if (header) {
		if (header->magic == MH_MAGIC_64)
			g_header_calls += 1;
	}
	return EXIT_SUCCESS;
}

/*
** test utils
*/

int		fd_to_str(int fd, char **out) {
	int c, bytes = 0;
	struct pollfd fds = {fd, POLLIN, 0};
	char *str = calloc(1, sizeof(char)), tmp[BUFSIZ] = {0};

	while (poll(&fds, 1, 0)) {
		c = read(fd, tmp, BUFSIZ - 1);
		if (c == -1){
			char *err __attribute__((unused)) = strerror(errno);
			return EXIT_FAILURE;
		}
		tmp[c] = '\0';
		char *next = malloc(c + bytes + 1);
		strcpy(next, str);
		strcat(next, tmp);
		free(str);
		str = next;
		bytes += c;
	}
	*out = str;
	return EXIT_SUCCESS;
}

int		swap_stdout(struct fixture *s) {
	if ((s->stdout = dup(STDOUT_FILENO) == -1) || pipe(s->stdout_fds) == -1)
		return EXIT_FAILURE;
	if (dup2(s->stdout_fds[1], STDOUT_FILENO) == -1)
		return MUNIT_ERROR;
	return EXIT_SUCCESS;
}

int		swap_stderr(struct fixture *s) {
	if ((s->stderr = dup(STDERR_FILENO)) == -1 || pipe(s->stderr_fds) == -1)
		return EXIT_FAILURE;
	if (dup2(s->stderr_fds[1], STDERR_FILENO) == -1)
		return MUNIT_ERROR;
	return EXIT_SUCCESS;
}

int		restore_stdout(struct fixture *s) {
	if (dup2(s->stdout, STDOUT_FILENO) == -1
		|| close(s->stdout_fds[0]) == -1
		|| close(s->stdout_fds[1]) == -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int		restore_stderr(struct fixture *s) {
	if (dup2(s->stderr, STDERR_FILENO) == -1
		|| close(s->stderr_fds[0]) == -1
		|| close(s->stderr_fds[1]) == -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
