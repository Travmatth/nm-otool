#ifndef TESTS_H
# define TESTS_H

#include "munit/munit.h"
#include <errno.h> // errno
#include <string.h> // bzero, strcpy, strcat
#include <poll.h> // poll
#include "../includes/common.h"
#include "../includes/otool.h"

/*
** test struct used for swapping & saving stdout output
*/

struct fixture {
	char	*otool_output;
	int		stdout_fds[2];
	int		stderr_fds[2];
	int		stdout;
	int		stderr;
	int		exit_status;
};

int		swap_stdout(struct fixture *s);
int		swap_stderr(struct fixture *s);
int		restore_stdout(struct fixture *s);
int		restore_stderr(struct fixture *s);

/*
** test/tests/utils.c
*/

int		verify_segments(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64);
int		verify_load_command(char *file, t_ctx *ctx, struct load_command *lc, void *addr);
int		verify_sections(char *file, t_ctx *ctx, struct section *section, struct section_64 *section_64);
int		verify_segment_address(char *file, t_ctx *ctx, struct segment_command *segment, struct segment_command_64 *segment_64);
int		verify_section_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64);
int		verify_header(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64);
int		verify_section64_address(char *file, t_ctx *ctx, struct section *sect, struct section_64 *sect64);
int		verify_header64(char *file, t_ctx *ctx, struct mach_header *header, struct mach_header_64 *header_64);
int		fd_to_str(int fd, char **out);
#endif
