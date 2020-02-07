/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_constructs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 19:21:46 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/06 21:48:01 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSE_CONSTRUCTS_H
# define PARSE_CONSTRUCTS_H

/*
** mach-o/fat.h - FAT_MAGIC/FAT_CIGAM
** mach-o/loader.h - MH_MAGIC/MH_CIGAM/MH_MAGIC_64/MH_CIGAM_64
** mach/machine.h - OSSwapInt32, cpu_type, cpu_subtype_t
*/

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach/machine.h>

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
	uint32_t						magic;
	size_t							size;
	int								has_x86_64;
	int								objects;
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
										, int swap
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

#endif
