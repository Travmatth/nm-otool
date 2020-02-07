/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:39 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/06 22:34:38 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMON_H
# define FT_COMMON_H

# ifndef LIBFT_H
#  include "../libftprintf/srcs/includes/ft_printf.h"
# endif

# ifndef PARSE_CONSTRUCTS_H
#  include "parse_constructs.h"
# endif

/*
** fcntl.h - open
** sys/stat.h - fstat
** sys/mman.h - mmap/PROT_READ/PROT_WRITE/MAP_PRIVATE/MAP_FAILED
** ar.h - ARMAG/SARMAG/AR_EFMT1/struct ar_hdr
*/

# include <mach-o/swap.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <ar.h>

/*
** Check that function exits successfully
*/

# define OK(x) ((x == EXIT_SUCCESS))

/*
** Detect computer is 64bit
*/

# define HOST_64BIT (sizeof(void*) == 8)

/*
** Options used when mmapping potential binary files to memory pointers
*/

# define MMAP_PROT (PROT_READ)
# define MMAP_FLAGS (MAP_PRIVATE)

/*
** Translating memory into hex representation
*/

# define HEX_CHARS ("0123456789abcdef")

/*
** Maximum power of 2 that universal files objects may be aligned to
*/

# define MAX_SECTION_ALIGNMENT 15

/*
** common/validate_file.c
*/

int			determine_magic(char *file, int *flags);
int			validate_file(char *file, t_ctx *ctx, int flags);
int			validate_file_flags(char *file, t_ctx *ctx, int *flags);
int			validate_unknown(char *file, t_ctx *ctx);

/*
** common/validate_archive.c
*/

int			validate_extended_archive(char *file, t_ctx *ctx);

/*
** common/validate_i386.c
*/

int			validate_mach_i386(char *file, t_ctx *ctx, int flags);

/*
** common/validate_x86_64.c
*/

int			validate_mach_x86_64(char *file, t_ctx *ctx, int flags);

/*
** common/validate_fat.c
*/

int			validate_fat(char *file, t_ctx *ctx, int flags);

/*
** common/format.c
*/

int			print_memory_buf(int swapped, char mem_buf[33]);
void		format_pointer(uint64_t addr, char ptr_buf[], int is_64);
void		format_mem(char *file
						, uint64_t *offset
						, uint64_t size
						, char mem_buf[]);

/*
** common/magics.c
*/

int			is_fat32(int *flags, uint32_t magic);
int			is_fat64(int *flags, uint32_t magic);
int			is_mach64(int *flags, uint32_t magic);
int			is_mach32(int *flags, uint32_t magic);
int			is_archive(char *file, int *flags);

/*
** common/utils.c
*/

uint32_t	uint32_pow(uint32_t base, uint32_t power);
void		print_section_prologue(char *file, t_ctx *ctx);
uint32_t	swap(t_ctx *ctx, uint32_t val);
int			get_file(int argc, char **argv, char **envp, t_ctx *ctx);
int			cleanup_ctx(t_ctx *ctx);


/*
** common/file_multiplexer
*/

int			file_multiplexer(char *file, t_ctx *ctx, t_dump_fxs *dump, int flags);
int			validate_multiplex(char *file, t_ctx *ctx, t_dump_fxs *dump);

/*
** common/mach_i386.c
*/

int			dump_mach_i386(char *file, t_ctx *ctx, t_dump_fxs *fxs, int flags);

/*
** common/mach_x86_64.c
*/

int			dump_mach_x86_64(char *file, t_ctx *ctx, t_dump_fxs *fxs);

/*
** common/fat.c
*/

int			dump_fat_bin(char *file, t_ctx *ctx, t_dump_fxs *fxs);
int			dump_fat64_bin(char *file, t_ctx *ctx, t_dump_fxs *fxs);

/*
** Debug statements used when compiled with __DEBUG__ variable defined
*/

# ifdef __DEBUG__
#  define DEBUG_LOG(fmt, ...) ft_dprintf(STDERR_FILENO, fmt, __VA_ARGS__)
#  define DEBUG_PRINT(str) ft_dprintf(STDERR_FILENO, str)
# else
#  define DEBUG_LOG(fmt, ...) PASS
#  define DEBUG_PRINT(str) PASS
# endif
#endif
