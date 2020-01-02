/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:19:02 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/01 18:04:17 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

int		validate_symtab_entries(char *file, struct symtab_command *symtab, int flags)
{
	uint32_t		i;
	uint32_t		offset;
	struct nlist	*nlist;
	struct nlist_64	*nlist64;

	i = 0;
	offset = symtab->symoff;
	while (i++ < symtab->nsyms)
	{
		if (flags & IS_32)
		{
			nlist = (struct nlist *)(file + offset);
			if (symtab->stroff + nlist->n_un.n_strx > symtab->strsize)
				return (EXIT_FAILURE);
			offset += sizeof(struct nlist);
		}
		else if (flags & IS_64)
		{
			nlist64 = (struct nlist_64 *)(file + offset);
			if (nlist64->n_un.n_strx > symtab->strsize)
				return (EXIT_FAILURE);
			offset += sizeof(struct nlist_64);
		}
	}
	return (EXIT_SUCCESS);
}

int		validate_mach64(char *file, t_ctx *ctx)
{
	struct mach_header_64	*hdr;
	t_lcommand				u;
	uint64_t				i;
	uint64_t				offset;

	i = 0;
	hdr = (struct mach_header_64*)file;
	offset = sizeof(struct mach_header_64);
	while (i++ < hdr->ncmds)
	{
		if ((file + offset + sizeof(struct load_command)) >
			(file + sizeof(struct mach_header_64) + hdr->sizeofcmds))
			return (EXIT_FAILURE);
		u.load = (struct load_command*)(file + offset);
		if (u.load->cmdsize % 8)
			return (EXIT_FAILURE);
		if (u.load->cmd == LC_SEGMENT_64)
		{
			if ((u.segment64->fileoff + u.segment64->filesize > ctx->size)
				|| (u.segment64->filesize > u.segment64->vmsize))
				return (EXIT_FAILURE);
		}
		else if (u.load->cmd == LC_SYMTAB)
		{
			if ((u.symtab->stroff + u.symtab->strsize > ctx->size)
				|| validate_symtab_entries(file, u.symtab, ctx->flags))
				return (EXIT_FAILURE);
		}
		offset += u.load->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int		validate_file(char *file, t_ctx *ctx)
{
	if (ctx->flags & IS_64)
		return (validate_mach64(file, ctx));
	return (EXIT_SUCCESS);
}
