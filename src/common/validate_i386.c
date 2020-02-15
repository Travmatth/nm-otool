/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_i386.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:23:12 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 22:47:00 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

static int		validate_i386_symtab_entries(char *file
								, struct symtab_command *symtab
								, int flags)
{
	int				status;
	uint32_t		i;
	struct nlist	*nlist;

	i = 0;
	status = EXIT_SUCCESS;
	if ((nlist = ft_memdup(file + symtab->symoff
		, sizeof(struct nlist) * symtab->nsyms)) == NULL)
		return (EXIT_FAILURE);
	if (flags & SWAP)
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

int				validate_symtab_i386(t_ctx *ctx
						, struct symtab_command	*symtab
						, struct mach_header *header
						, int flags)
{
	struct symtab_command	sym;

	sym = *symtab;
	if (flags & SWAP)
		swap_symtab_command(&sym, NX_UnknownByteOrder);
	if ((sym.symoff > ctx->size)
		|| (sym.symoff >= header->sizeofcmds && sym.symoff <
		(sizeof(struct mach_header_64) + header->sizeofcmds))
		|| (sym.symoff + sym.nsyms * sizeof(struct nlist_64) >
			header->sizeofcmds &&
			sym.symoff + sym.nsyms * sizeof(struct nlist_64) <
			(sizeof(struct mach_header_64) + header->sizeofcmds))
		|| (sym.symoff <= header->sizeofcmds &&
		sym.symoff + (sym.nsyms) * sizeof(struct nlist_64) >=
			(sizeof(struct mach_header_64) + header->sizeofcmds))
		|| ((sym.stroff + sym.strsize > ctx->size)
			|| validate_i386_symtab_entries(ctx->file, &sym, flags)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int		validate_i386_sections(struct segment_command *segment
									, t_ctx *ctx
									, int flags)
{
	int				status;
	uint32_t		i;
	struct section	*section;

	i = 0;
	status = EXIT_SUCCESS;
	section = ft_memdup(ctx->file + ctx->offset + sizeof(struct segment_command)
		, sizeof(struct section) * segment->nsects);
	if (section == NULL)
		return (EXIT_FAILURE);
	else if (flags & SWAP)
		swap_section(section, segment->nsects, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < segment->nsects)
	{
		if (section[i++].size > segment->filesize)
			status = EXIT_FAILURE;
	}
	free(section);
	return (status);
}

int				validate_i386_segment(struct segment_command *seg
							, t_ctx *ctx
							, int flags)
{
	struct segment_command	segment;

	segment = *seg;
	if (flags & SWAP)
		swap_segment_command(&segment, NX_UnknownByteOrder);
	if (segment.nsects * sizeof(struct section) >
		segment.cmdsize - sizeof(struct segment_command))
		return (EXIT_FAILURE);
	else if (segment.fileoff + segment.filesize > ctx->size)
		return (EXIT_FAILURE);
	else if (segment.filesize > segment.vmsize)
		return (EXIT_FAILURE);
	else if (validate_i386_sections(&segment, ctx, flags) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ctx->hook.i386_segment)
		return (ctx->hook.i386_segment(seg, ctx, flags));
	return (EXIT_SUCCESS);
}

int				validate_mach_i386(char *file, t_ctx *ctx, int flags)
{
	uint32_t			i;
	t_header			h;
	struct load_command	lc;
	t_lcommand			u;

	i = 0;
	h.header = *(struct mach_header*)file;
	if (flags & SWAP)
		swap_mach_header(&h.header, NX_UnknownByteOrder);
	ctx->offset = sizeof(struct mach_header);
	while (i++ < h.header.ncmds)
	{
		if (file + ctx->offset + sizeof(struct load_command) >
			file + sizeof(struct mach_header) + h.header.sizeofcmds)
			return (EXIT_FAILURE);
		u.load = *(struct load_command*)(file + ctx->offset);
		if (flags & SWAP)
			swap_load_command(&u.load, NX_UnknownByteOrder);
		if (validate_load_command(h, ctx, flags, u) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (ctx->hook.load_command
			&& ctx->hook.load_command(&u, ctx, flags))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
