/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_i386.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:23:12 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/14 00:54:42 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

static int		validate_symtab_entries(char *file
								, t_ctx *ctx
								, struct symtab_command *symtab)
{
	int				status;
	uint32_t		i;
	struct nlist	*nlist;

	i = 0;
	status = EXIT_SUCCESS;
	if ((nlist = ft_memdup(file + symtab->symoff
		, sizeof(struct nlist) * symtab->nsyms)) == NULL)
		return (EXIT_FAILURE);
	if (ctx->flags & SWAP)
		swap_nlist(nlist, symtab->nsyms, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < symtab->nsyms)
	{
		if (nlist[i].n_un.n_strx > symtab->strsize)
			status = EXIT_FAILURE;
		i += 1;
	}
	free(nlist);
	return (EXIT_SUCCESS);
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
						, struct mach_header *header)
{
	struct symtab_command	sym;

	sym = *symtab;
	if (ctx->flags & SWAP)
		swap_symtab_command(&sym, NX_UnknownByteOrder);
	if (sym.symoff > ctx->size)
		return (EXIT_FAILURE);
	else if (sym.symoff >= 0 && sym.symoff <
		(sizeof(struct mach_header_64) + header->sizeofcmds))
		return (EXIT_FAILURE);
	else if (sym.symoff + sym.nsyms * sizeof(struct nlist_64) > 0 &&
		sym.symoff + sym.nsyms * sizeof(struct nlist_64) <
			(sizeof(struct mach_header_64) + header->sizeofcmds))
		return (EXIT_FAILURE);
	else if (sym.symoff <= 0 &&
		sym.symoff + (sym.nsyms) * sizeof(struct nlist_64) >=
			(sizeof(struct mach_header_64) + header->sizeofcmds))
		return (EXIT_FAILURE);
	else if ((sym.stroff + sym.strsize > ctx->size)
		|| validate_symtab_entries(file, ctx, &sym))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int		validate_i386_sections(char *file, t_ctx *ctx, struct segment_command *segment, ptrdiff_t base)
{
	int				status;
	uint32_t		i;
	uint32_t		offset;
	struct section	*section;

	status = EXIT_SUCCESS;
	i = 0;
	offset = base + sizeof(struct segment_command);
	if ((section = ft_memdup(file + offset
		, sizeof(struct section) * segment->nsects)) == NULL)
		return (EXIT_FAILURE);
	if (ctx->flags & SWAP)
		swap_section(section, segment->nsects, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < segment->nsects)
	{
		if (section[i++].size > segment->filesize)
			status = EXIT_FAILURE;
	}
	free(section);
	return (status);
}

static int		validate_segment(char *file, t_ctx *ctx, struct segment_command *seg)
{
	struct segment_command	segment;
	int						status;

	status = EXIT_SUCCESS;
	segment = *seg;
	if (ctx->flags & SWAP)
		swap_segment_command(&segment, NX_UnknownByteOrder);
	if (segment.nsects * sizeof(struct section) >
		segment.cmdsize - sizeof(struct segment_command))
		status = EXIT_FAILURE;
	else if (segment.fileoff + segment.filesize > ctx->size)
		status = EXIT_FAILURE;
	else if (segment.filesize > segment.vmsize)
		status = EXIT_FAILURE;
	else
		status = validate_i386_sections(file, ctx, &segment, (char*)seg - file);
	return (status);
}

int		validate_mach_i386(char *file, t_ctx *ctx)
{
	uint32_t			i;
	uint32_t			offset;
	struct mach_header	header;
	struct load_command	lc;

	i = 0;
	header = *(struct mach_header*)file;
	if (ctx->flags & SWAP)
		swap_mach_header(&header, NX_UnknownByteOrder);
	offset = sizeof(struct mach_header);
	while (i < header.ncmds)
	{
		if (file + offset + sizeof(struct load_command) > file + sizeof(struct mach_header) + header.sizeofcmds)
			return (EXIT_FAILURE);
		lc = *(struct load_command*)(file + offset);
		if (ctx->flags & SWAP)
			swap_load_command(&lc, NX_UnknownByteOrder);
		if (lc.cmdsize % 4)
			return (EXIT_FAILURE);
		else if (lc.cmd == LC_SEGMENT && validate_segment(file, ctx
				, (struct segment_command*)(file + offset)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (lc.cmd == LC_SYMTAB && validate_symtab(file, ctx
				, (struct symtab_command*)(file + offset), &header) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		offset += lc.cmdsize;
		i += 1;
	}
	return (EXIT_SUCCESS);
}
