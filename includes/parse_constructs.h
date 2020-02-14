/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_constructs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 19:21:46 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 15:29:01 by tmatthew         ###   ########.fr       */
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
** Record what types of objects to be parsed and printed
** TEXT_SECTIONS: print __TEXT__text sections of macho objects
*/

enum								e_targets
{
	TEXT_SECTIONS = (1u << 0),
};

/*
** Out structs store information of hooked objects for use in printing
*/

typedef struct						s_i386_text
{
	struct section					**sections;
	char							**data;
	int								*flags;
}									t_i386_text;

typedef struct						s_x86_64_text
{
	struct section_64				**sections;
	char							**data;
	int								*flags;
}									t_x86_64_text;

/*
** Struct to hold the different sections and segments parsed from the file
**
*/

typedef struct						s_out
{
	t_i386_text						i386_text;
	t_x86_64_text					x86_64_text;
}									t_out;

/*
** Hook function used to save the needed segments/sections of the input file
** for later printing
*/

struct s_ctx;

typedef int							(*t_i386_header_hook)(struct mach_header *header
														, struct s_ctx *ctx
														, int flags);

typedef int							(*t_x86_64_header_hook)(struct mach_header_64 *header
														, struct s_ctx *ctx
														, int flags);

typedef int							(*t_i386_segment_hook)(struct segment_command *segment
														, struct s_ctx *ctx
														, int flags);

typedef int							(*t_x86_64_segment_hook)(struct segment_command_64 *segment
														, struct s_ctx *ctx
														, int flags);

typedef int							(*t_i386_section_hook)(struct section *sect
														, struct s_ctx *ctx
														, int flags);

typedef int							(*t_x86_64_section_hook)(struct section_64 *sect
														, struct s_ctx *ctx
														, int flags);

typedef struct						s_hook
{
	t_i386_header_hook				i386_header;
	t_x86_64_header_hook			x86_64_header;
	t_i386_segment_hook				i386_segment;
	t_x86_64_segment_hook			x86_64_segment;
	t_i386_section_hook				i386_section;
	t_x86_64_section_hook			x86_64_section;
}									t_hook;

/*
** SWAP: endianness of data opposite of current architecture
** IS_32: binary file for 32bit systems
** IS_FAT: binary file for FAT format
** IS_ARCHIVE: binary file for archive format
** IS_EXTENDED_ARCHIVE: binary file for extended format
** IS_64: binary file for x86_64 format
** IS_MACH: binary file for macho format
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
** file: binary filename being parsed
** size: size of binary file in bytes
** targets: types of objects to parse
*/

typedef struct						s_ctx
{
	char							*file;
	char							*filename;
	size_t							size;
	int								targets;
	t_out							out;
	t_hook							hook;
}									t_ctx;

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
