/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:39 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/20 13:13:28 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMON_H
# define FT_COMMON_H

# ifndef LIBFT_H
#  include "../libftprintf/srcs/includes/ft_printf.h"
# endif

/*
** fcntl.h - open
** sys/stat.h - fstat
** sys/mman.h - mmap/PROT_READ/PROT_WRITE/MAP_PRIVATE/MAP_FAILED
** mach-o/fat.h - FAT_MAGIC/FAT_CIGAM
** mach-o/loader.h - MH_MAGIC/MH_CIGAM/MH_MAGIC_64/MH_CIGAM_64
** ar.h - ARMAG/SARMAG/AR_EFMT1/struct ar_hdr
*/

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <ar.h>

/*
** Options used when mmapping potential binary files to memory pointers
*/

# define MMAP_PROT (PROT_READ | PROT_WRITE)
# define MMAP_FLAGS (MAP_PRIVATE)

/*
** IS_SWAPPED: endianness of data opposite of current architecture
** IS_32: binary file targeted for 32bit systems
** IS_FAT: binary file is in FAT format
*/

enum	e_flags
{
	IS_SWAPPED = (1u << 0),
	IS_32 = (1u << 1),
	IS_FAT = (1u << 2),
	IS_ARCHIVE = (1u << 3),
	IS_EXTENDED_ARCHIVE = (1u << 4),
};

/*
** t_ctx
** file: binary file being parsed
** flags: e_flags options
** magic: magic number describing binary file format & endianness
** size: size of binary file in bytes
*/

typedef struct	s_ctx
{
	char		*file;
	int			flags;
	uint32_t	magic;
	size_t		size;
}				t_ctx;

/*
** signature of functions passed into dump_*_lcmds functions
*/

typedef int		(*t_seg_func)(t_ctx *ctx, struct segment_command *segment);
typedef int		(*t_seg64_func)(t_ctx *ctx, struct segment_command_64 *segment);

/*
** common/magics.c
*/

int				is_fat32(t_ctx *ctx, uint32_t magic);
int				is_fat64(t_ctx *ctx, uint32_t magic);
int				is_mach64(t_ctx *ctx, uint32_t magic);
int				is_mach32(t_ctx *ctx, uint32_t magic);
int				is_archive(t_ctx *ctx);

/*
** common/utils.c
*/

int				get_file(int argc, char **argv, char **envp, t_ctx *ctx);
int				determine_file(t_ctx *ctx);
uint32_t		swap_uint32(uint32_t old);
uint64_t		swap_uint64(uint64_t old);
int				cleanup_ctx(t_ctx *ctx);

/*
** common/mach-o.c
*/

int				dump_mach_segs(t_ctx *ctx, t_seg_func f, t_seg64_func f64);


/*
** common/fat.c
*/

int				dump_fat_segs(t_ctx *ctx, t_seg_func f, t_seg64_func f64);

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
