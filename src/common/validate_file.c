/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:19:02 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/07 14:18:38 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

uint32_t	swap(t_ctx *ctx, uint32_t val)
{
	return ((ctx->flags & SWAP) ? OSSwapInt32(val) : val);
}

int		validate_i386_sections(char *file, t_ctx *ctx, t_lcommand u)
{
	uint64_t		i;
	uint64_t		offset;
	struct section	*section;

	i = 0;
	offset = ((char*)u.segment - file) + sizeof(struct segment_command_64);
	while (i++ < swap(ctx, u.segment->nsects))
	{
		section = (struct section*)(file + offset);
		if (swap(ctx, section->size) > swap(ctx, u.segment->filesize))
			return (EXIT_FAILURE);
		offset += sizeof(struct section);
	}
	return (EXIT_SUCCESS);
}

int		validate_x86_64_sections(char *file, t_lcommand u)
{
	uint64_t			i;
	uint64_t			offset;
	struct section_64	*section;

	i = 0;
	offset = ((char*)u.segment64 - file) + sizeof(struct segment_command_64);
	while (i++ < u.segment64->nsects)
	{
		section = (struct section_64*)(file + offset);
		if (section->size > u.segment64->filesize)
			return (EXIT_FAILURE);
		offset += sizeof(struct section_64);
	}
	return (EXIT_SUCCESS);
}

int		validate_symtab_entries(char *file, t_ctx *ctx, struct symtab_command *symtab)
{
	uint32_t		i;
	uint32_t		offset;
	struct nlist	*nlist;
	struct nlist_64	*nlist64;

	i = 0;
	offset = symtab->symoff;
	while (i++ < symtab->nsyms)
	{
		if (ctx->flags & IS_32)
		{
			nlist = (struct nlist *)(file + offset);
			if (swap(ctx, nlist->n_un.n_strx) > swap(ctx, symtab->strsize))
				return (EXIT_FAILURE);
			offset += sizeof(struct nlist);
		}
		else if (ctx->flags & IS_64)
		{
			nlist64 = (struct nlist_64 *)(file + offset);
			if (nlist64->n_un.n_strx > symtab->strsize)
				return (EXIT_FAILURE);
			offset += sizeof(struct nlist_64);
		}
	}
	return (EXIT_SUCCESS);
}

int		validate_mach_i386(char *file, t_ctx *ctx)
{
	struct mach_header	*hdr;
	t_lcommand				u;
	uint64_t				i;
	uint64_t				offset;

	i = 0;
	hdr = (struct mach_header*)file;
	offset = sizeof(struct mach_header);
	while (i++ < swap(ctx, hdr->ncmds))
	{
		if ((file + offset + sizeof(struct load_command)) >
			(file + sizeof(struct mach_header) + swap(ctx, hdr->sizeofcmds)))
			return (EXIT_FAILURE);
		u.load = (struct load_command*)(file + offset);
		if (swap(ctx, u.load->cmdsize) % 4)
			return (EXIT_FAILURE);
		if (u.load->cmd == LC_SEGMENT)
		{
			if ((swap(ctx, u.segment->nsects) * sizeof(struct section) >
				swap(ctx, u.segment->cmdsize) - sizeof(struct segment_command))
				|| (swap(ctx, u.segment->fileoff) + swap(ctx, u.segment->filesize) > ctx->size)
				|| (swap(ctx, u.segment->filesize) > swap(ctx, u.segment->vmsize))
				|| !OK(validate_i386_sections(file, ctx, u)))
				return (EXIT_FAILURE);
		}
		else if (u.load->cmd == LC_SYMTAB)
		{
			// if symtab starts before end of load commands
			if (swap(ctx, u.symtab->symoff) >= 0 && swap(ctx, u.symtab->symoff) < (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			// if symtab ends before end of load commands
			if (swap(ctx, u.symtab->symoff) + (swap(ctx, u.symtab->nsyms) * sizeof(struct nlist_64)) > 0 &&
				swap(ctx, u.symtab->symoff) + (swap(ctx, u.symtab->nsyms) * sizeof(struct nlist_64)) < (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			// symtab starts before the header and end of symtab is after end of load commands
			if (swap(ctx, u.symtab->symoff) <= 0 &&
				swap(ctx, u.symtab->symoff) + (swap(ctx, u.symtab->nsyms) * sizeof(struct nlist_64)) >= (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			if ((swap(ctx, u.symtab->stroff) + swap(ctx, u.symtab->strsize) > ctx->size)
				|| validate_symtab_entries(file, ctx, u.symtab))
				return (EXIT_FAILURE);
		}
		offset += swap(ctx, u.load->cmdsize);
	}
	return (EXIT_SUCCESS);
}

int		validate_mach_x86_64(char *file, t_ctx *ctx)
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
			if ((u.segment64->nsects * sizeof(struct section_64) >
				u.segment64->cmdsize - sizeof(struct segment_command_64))
				|| (u.segment64->fileoff + u.segment64->filesize > ctx->size)
				|| (u.segment64->filesize > u.segment64->vmsize)
				|| !OK(validate_x86_64_sections(file, u)))
				return (EXIT_FAILURE);
		}
		else if (u.load->cmd == LC_SYMTAB)
		{
			// if symtab starts before end of load commands
			if (u.symtab->symoff >= 0 && u.symtab->symoff < (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			// if symtab ends before end of load commands
			if (u.symtab->symoff + (u.symtab->nsyms * sizeof(struct nlist_64)) > 0 &&
				u.symtab->symoff + (u.symtab->nsyms * sizeof(struct nlist_64)) < (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			// symtab starts before the header and end of symtab is after end of load commands
			if (u.symtab->symoff <= 0 &&
				u.symtab->symoff + (u.symtab->nsyms * sizeof(struct nlist_64)) >= (sizeof(struct mach_header_64) + hdr->sizeofcmds))
				return (EXIT_FAILURE);
			if ((u.symtab->stroff + u.symtab->strsize > ctx->size)
				|| validate_symtab_entries(file, ctx, u.symtab))
				return (EXIT_FAILURE);
		}
		offset += u.load->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int		validate_mach_fat(char *file, t_ctx *ctx)
{
	(void)file;
	(void)ctx;
	return (EXIT_SUCCESS);
}

int		validate_file(char *file, t_ctx *ctx)
{
	if (ctx->flags & IS_FAT)
		return (validate_mach_fat(file, ctx));
	else if ((ctx->flags & IS_MACH) && (ctx->flags & IS_64))
		return (validate_mach_x86_64(file, ctx));
	else if ((ctx->flags & IS_MACH) && (ctx->flags & IS_32))
		return (validate_mach_i386(file, ctx));
	return (EXIT_FAILURE);
}
