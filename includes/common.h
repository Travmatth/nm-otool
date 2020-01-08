/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:39 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/08 12:43:57 by tmatthew         ###   ########.fr       */
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
** mach/machine.h - OSSwapInt32, cpu_type, cpu_subtype_t
*/

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/fat.h>
# include <mach-o/swap.h>
# include <mach-o/loader.h>
# include <ar.h>
# include <mach/machine.h>

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
** SWAP: endianness of data opposite of current architecture
** IS_32: binary file targeted for 32bit systems
** IS_FAT: binary file is in FAT format
*/

enum								e_flags
{
	SWAP = (1u << 0),
	IS_32 = (1u << 1),
	IS_FAT = (1u << 2),
	IS_ARCHIVE = (1u << 3),
	IS_EXTENDED_ARCHIVE = (1u << 4),
	IS_64 = (1u << 5),
	IS_MACH = (1u << 6),
};

/*
** t_ctx
** file: binary file being parsed
** flags: e_flags options
** magic: magic number describing binary file format & endianness
** size: size of binary file in bytes
*/

typedef struct						s_ctx
{
	char							*file;
	char							*filename;
	int								flags;
	uint32_t						magic;
	size_t							size;
}									t_ctx;

/*
** signature of functions passed into dump_* functions
*/

typedef int							(*t_hdr_f)(char *file
										, t_ctx *ctx
										, struct mach_header *header
										, struct mach_header_64 *header_64);
typedef int							(*t_seg_f)(char *file
										, t_ctx *ctx
										, struct segment_command *segment
										, struct segment_command_64 *segment_64);
typedef int							(*t_sec_i386_f)(char *file
										, t_ctx *ctx
										, struct section *section);
typedef int							(*t_sec_x86_64_f)(char *file
										, struct section_64 *section);
typedef int							(*t_lc_f)(char *file
										, t_ctx *ctx
										, struct load_command *lc
										, void *addr);

/*
** struct containing functions called when dumping different parts of binary
*/

typedef struct						s_dump_fxs
{
	t_hdr_f							header;
	t_seg_f							segment;
	t_sec_i386_f					i386_section;
	t_sec_x86_64_f					x86_64_section;
	t_lc_f							load;
}									t_dump_fxs;

/*
** struct containing important parts of mach-o binaries
*/

typedef struct						s_mach_o_32
{
	ptrdiff_t						offset;
	uint32_t						num_commands;
	struct mach_header				*hdr;
	struct load_command				*lc;
	struct segment_command			*sc;
}									t_macho32;

typedef struct						s_mach_o_64
{
	ptrdiff_t						offset;
	uint32_t						num_commands;
	struct mach_header_64			*hdr;
	struct load_command				*lc;
	struct segment_command_64		*sc;
}									t_macho64;

typedef	union							u_nlist
{
	struct nlist						*nlist;
	struct nlist_64						*nlist64;
}										t_nlist;

typedef union							u_section
{
	struct section						*section;
	struct section_64					*section64;
}										t_section;

typedef union							u_lcommand
{
	struct load_command					*load;
	struct segment_command				*segment;
	struct segment_command_64			*segment64;
	struct symtab_command				*symtab;
	struct symseg_command				*symseg;
	struct thread_command				*thread;
	struct fvmlib_command				*fvmlib;
	struct ident_command				*ident;
	struct fvmfile_command				*fvmfile;
	struct dysymtab_command				*dysymtab;
	struct dylib_command				*dylib;
	struct dylinker_command				*dylinker;
	struct prebound_dylib_command		*prebound;
	struct routines_command				*routines;
	struct routines_command_64			*routines64;
	struct encryption_info_command		*info;
	struct encryption_info_command_64	*info64;
}										t_lcommand;

/*
** common/validate_file.c
*/

int										validate_file(char *file, t_ctx *ctx, int classify);

/*
** common/format.c
*/

int										print_memory_buf(int swapped
											, char mem_buf[33]);
void									format_pointer(uint64_t addr
											, char ptr_buf[]
											, int is_64);
void									format_mem(char *binary
											, uint64_t *offset
											, uint64_t size
											, char mem_buf[]);

/*
** common/magics.c
*/

int										is_fat32(t_ctx *ctx, uint32_t magic);
int										is_fat64(t_ctx *ctx, uint32_t magic);
int										is_mach64(t_ctx *ctx, uint32_t magic);
int										is_mach32(t_ctx *ctx, uint32_t magic);
int										is_archive(t_ctx *ctx);

/*
** common/utils.c
*/

int										get_file(int argc
											, char **argv
											, char **envp
											, t_ctx *ctx);
int										determine_file(char *file, t_ctx *ctx);
int										cleanup_ctx(t_ctx *ctx);


/*
** common/mach_x86_64_sections
*/

int										dump_i386_sections(char *file
											, t_ctx *ctx
											, struct segment_command *segment
											, t_dump_fxs *dump);
int										dump_x86_64_sections(char *file
											, struct segment_command_64 *segment
											, t_dump_fxs *dump);

/*
** common/file_multiplexer
*/

int										file_multiplexer(char *file
											, t_ctx *ctx
											, t_dump_fxs *dump
											, int validate);

/*
** common/mach-o.c
*/

int										dump_macho_bin(char *file
											, t_ctx *ctx
											, t_dump_fxs *fxs);
int										dump_macho64_bin(char *file
											, t_ctx *ctx
											, t_dump_fxs *fxs);

/*
** common/fat.c
*/

int										dump_fat_bin(char *file
											, t_ctx *ctx
											, t_dump_fxs *fxs);
int										dump_fat64_bin(char *file
											, t_ctx *ctx
											, t_dump_fxs *fxs);

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
