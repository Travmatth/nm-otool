/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_x86_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 22:46:54 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

static int		validate_x86_64_symtab_entries(char *file
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

int				validate_symtab_x86_64(t_ctx *ctx
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
			|| validate_x86_64_symtab_entries(ctx->file, &sym, flags)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int		validate_i386_sections(struct segment_command_64 *segment
									, t_ctx *ctx
									, int flags)
{
	int					status;
	uint32_t			i;
	struct section_64	*section;

	i = 0;
	status = EXIT_SUCCESS;
	section = ft_memdup(ctx->file
		+ ctx->offset + sizeof(struct segment_command_64)
		, sizeof(struct section_64) * segment->nsects);
	if (section == NULL)
		return (EXIT_FAILURE);
	else if (flags & SWAP)
		swap_section_64(section, segment->nsects, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < segment->nsects)
	{
		if (section[i++].size > segment->filesize)
			status = EXIT_FAILURE;
	}
	free(section);
	return (status);
}

int				validate_x86_64_segment(struct segment_command_64 *seg
									, t_ctx *ctx
									, int flags)
{
	struct segment_command_64	segment;

	segment = *seg;
	if (flags & SWAP)
		swap_segment_command_64(&segment, NX_UnknownByteOrder);
	if (segment.nsects * sizeof(struct section_64) >
		segment.cmdsize - sizeof(struct segment_command_64))
		return (EXIT_FAILURE);
	else if (segment.fileoff + segment.filesize > ctx->size)
		return (EXIT_FAILURE);
	else if (segment.filesize > segment.vmsize)
		return (EXIT_FAILURE);
	else if (validate_x86_64_sections(&segment, ctx, flags) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ctx->hook.i386_segment)
		return (ctx->hook.x86_64_segment(seg, ctx, flags));
	return (EXIT_SUCCESS);
}

int				validate_mach_x86_64(char *file, t_ctx *ctx, int flags)
{
	uint32_t			i;
	t_header			h;
	struct load_command	lc;
	t_lcommand			u;

	i = 0;
	h.header_64 = *(struct mach_header_64*)file;
	if (flags & SWAP)
		swap_mach_header(&h.header_64, NX_UnknownByteOrder);
	ctx->offset = sizeof(struct mach_header_64);
	while (i++ < h.header_64.ncmds)
	{
		if (file + ctx->offset + sizeof(struct load_command) >
			file + sizeof(struct mach_header_64) + h.header_64.sizeofcmds)
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
