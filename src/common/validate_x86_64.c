/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_x86_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/13 22:41:16 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

static int		validate_symtab_entries(char *file
								, t_ctx *ctx
								, struct symtab_command *symtab)
{
	int				status;
	uint32_t		i;
	struct nlist_64	*nlist_64;

	i = 0;
	status = EXIT_SUCCESS;
	if ((nlist_64 = ft_memdup(file + symtab->symoff
		, sizeof(struct nlist_64) * symtab->nsyms)) == NULL)
		return (EXIT_FAILURE);
	if (ctx->flags & SWAP)
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
						, struct mach_header_64 *header)
{
	struct symtab_command	sym;

	sym = *symtab;
	if (ctx->flags & SWAP)
		swap_symtab_command(&sym, NX_UnknownByteOrder);
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

static int		validate_i386_sections(char *file, t_ctx *ctx, struct segment_command_64 *segment, ptrdiff_t base)
{
	int					status;
	uint32_t			i;
	uint32_t			offset;
	struct section_64	*section;

	status = EXIT_SUCCESS;
	i = 0;
	offset = base + sizeof(struct segment_command_64);
	if ((section = ft_memdup(file + offset
		, sizeof(struct section_64) * segment->nsects)) == NULL)
		return (EXIT_FAILURE);
	if (ctx->flags & SWAP)
		swap_section_64(section, segment->nsects, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < segment->nsects)
	{
		if (section[i++].size > segment->filesize)
			status = EXIT_FAILURE;
	}
	free(section);
	return (status);
}

static int		validate_segment(char *file, t_ctx *ctx, struct segment_command_64 *seg)
{
	struct segment_command_64	segment;
	int						status;

	status = EXIT_SUCCESS;
	segment = *seg;
	if (ctx->flags & SWAP)
		swap_segment_command_64(&segment, NX_UnknownByteOrder);
	if (segment.nsects * sizeof(struct section) >
		segment.cmdsize - sizeof(struct segment_command_64))
		status = EXIT_FAILURE;
	else if (segment.fileoff + segment.filesize > ctx->size)
		status = EXIT_FAILURE;
	else if (segment.filesize > segment.vmsize)
		status = EXIT_FAILURE;
	else
		status = validate_i386_sections(file, ctx, &segment, (char*)seg - file);
	return (status);
}

int		validate_mach_x86_64(char *file, t_ctx *ctx)
{
	uint32_t				i;
	uint32_t				offset;
	struct mach_header_64	header;
	struct load_command		lc;

	i = 0;
	header = *(struct mach_header_64*)file;
	if (ctx->flags & SWAP)
		swap_mach_header_64(&header, NX_UnknownByteOrder);
	offset = sizeof(struct mach_header_64);
	while (i < header.ncmds)
	{
		lc = *(struct load_command*)(file + offset);
		if (ctx->flags & SWAP)
			swap_load_command(&lc, NX_UnknownByteOrder);
		if (file + offset + sizeof(struct load_command) >
			file + sizeof(struct mach_header_64) + header.sizeofcmds)
			return (EXIT_FAILURE);
		else if (lc.cmdsize % 4)
			return (EXIT_FAILURE);
		else if (lc.cmd == LC_SEGMENT_64 && validate_segment(file, ctx
			, (struct segment_command_64*)(file + offset)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (lc.cmd == LC_SYMTAB && validate_symtab(file, ctx
			, (struct symtab_command*)(file + offset), &header) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		offset += lc.cmdsize;
		i += 1;
	}
	ctx->has_x86_64 = TRUE;
	return (EXIT_SUCCESS);
}
