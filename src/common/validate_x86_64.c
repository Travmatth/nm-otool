/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_x86_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 15:33:08 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

static int		validate_symtab_entries(char *file
								, struct symtab_command *symtab
								, int flags)
{
	int				status;
	uint32_t		i;
	struct nlist_64	*nlist_64;

	i = 0;
	status = EXIT_SUCCESS;
	if ((nlist_64 = ft_memdup(file + symtab->symoff
		, sizeof(struct nlist_64) * symtab->nsyms)) == NULL)
		return (EXIT_FAILURE);
	if (flags & SWAP)
		swap_nlist_64(nlist_64, symtab->nsyms, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < symtab->nsyms)
	{
		if (nlist_64[i].n_un.n_strx > symtab->strsize)
			status = EXIT_FAILURE;
		i += 1;
	}
	free(nlist_64);
	return (status);
}

/*
** if symtab starts before end of load commands
** if symtab ends before end of load commands
** symtab starts before the header and end of symtab is after end of load
** commands
*/

static int		validate_symtab(char *file
						, t_ctx *ctx
						, struct symtab_command	*symtab
						, uint32_t sizeofcmds
						, int flags)
{
	struct symtab_command	sym;
	uint32_t				offset;

	sym = *symtab;
	offset = sym.symoff;
	if (flags & SWAP)
		swap_symtab_command(&sym, NX_UnknownByteOrder);
	if ((sym.symoff > ctx->size)
		|| (sym.symoff >= sizeofcmds && sym.symoff <
		(sizeof(struct mach_header_64) + sizeofcmds))
		|| (sym.symoff + sym.nsyms * sizeof(struct nlist_64) > sizeofcmds &&
		sym.symoff + sym.nsyms * sizeof(struct nlist_64) <
			(sizeof(struct mach_header_64) + sizeofcmds))
		|| (sym.symoff <= sizeofcmds &&
		sym.symoff + (sym.nsyms) * sizeof(struct nlist_64) >=
			(sizeof(struct mach_header_64) + sizeofcmds))
		|| ((sym.stroff + sym.strsize > ctx->size)
			|| validate_symtab_entries(file, &sym, flags)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int		validate_x86_64_sections(char *file, t_ctx *ctx, struct segment_command_64 *segment, ptrdiff_t base, int flags)
{
	int					status;
	uint32_t			i;
	uint32_t			offset;
	struct section_64	*sections;

	status = EXIT_SUCCESS;
	i = 0;
	offset = base + sizeof(struct segment_command_64);
	sections = ft_memdup(file + offset, sizeof(struct section_64) * segment->nsects);
	if (sections == NULL)
		return (EXIT_FAILURE);
	if (flags & SWAP)
		swap_section_64(sections, segment->nsects, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < segment->nsects)
	{
		if (sections[i].size > segment->filesize)
			status = EXIT_FAILURE;
		else if (ctx->hook.x86_64_section(&sections[i], ctx, flags))
			status = EXIT_FAILURE;
		i += 1;
	}
	free(sections);
	return (status);
}

static int		validate_segment(char *file, t_ctx *ctx, struct segment_command_64 *seg, int flags)
{
	struct segment_command_64	segment;
	int						status;

	status = EXIT_SUCCESS;
	segment = *seg;
	if (flags & SWAP)
		swap_segment_command_64(&segment, NX_UnknownByteOrder);
	if ((segment.nsects * sizeof(struct section) >
		segment.cmdsize - sizeof(struct segment_command_64))
		|| (segment.fileoff + segment.filesize > ctx->size)
		|| (segment.filesize > segment.vmsize))
		return (EXIT_FAILURE);
	return (validate_x86_64_sections(file, ctx, &segment, (char*)seg - file, flags));
}

int		validate_load_command(char *file, t_ctx *ctx, uint32_t *offset, uint32_t sizeofcmds, int flags)
{
	int							status;
	struct load_command			lc;
	struct segment_command_64	*seg_64;
	struct symtab_command		*symtab;

	lc = *(struct load_command*)(file + *offset);
	if (flags & SWAP)
		swap_load_command(&lc, NX_UnknownByteOrder);
	status = lc.cmdsize % 4 ? EXIT_FAILURE : EXIT_SUCCESS;
	if (status == EXIT_SUCCESS && lc.cmd == LC_SEGMENT_64)
	{
		seg_64 = (struct segment_command_64*)(file + *offset);
		status = validate_segment(file, ctx, seg_64, flags);
	}
	else if (status == EXIT_SUCCESS && lc.cmd == LC_SYMTAB)
	{
		symtab = (struct symtab_command*)(file + *offset);
		status = validate_symtab(file, ctx, symtab, sizeofcmds, flags);
	}
	*offset += lc.cmdsize;
	return (status);
}

int		validate_mach_x86_64(char *file, t_ctx *ctx, int flags)
{
	int						status;
	uint32_t				i;
	uint32_t				offset;
	struct mach_header_64	header;

	i = 0;
	header = *(struct mach_header_64*)file;
	if (flags & SWAP)
		swap_mach_header_64(&header, NX_UnknownByteOrder);
	offset = sizeof(struct mach_header_64);
	status = EXIT_SUCCESS;
	while (status == EXIT_SUCCESS && i++ < header.ncmds)
	{
		if (file + offset + sizeof(struct load_command) >
			file + sizeof(struct mach_header_64) + header.sizeofcmds)
			status = EXIT_FAILURE;
		else
			status = validate_load_command(file, ctx, &offset, header.sizeofcmds, flags);
	}
	return (status);
}
