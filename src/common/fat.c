/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/15 21:07:55 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

struct fat_header	*extract_fat_header(char *file, int flags)
{
	struct fat_header	*fat;

	fat = (struct fat_header*)malloc(sizeof(struct fat_header));
	if (fat == NULL)
		return (NULL);
	ft_memcpy(fat, file, sizeof(struct fat_header));
	if ((flags & IS_SWAPPED))
		fat->nfat_arch = OSSwapInt32(fat->nfat_arch);
	return (fat);
}

struct fat_arch		*extract_fat_arch(char *file, int flags, uint32_t i)
{
	struct fat_arch	*arch;
	size_t			offset;

	arch = (struct fat_arch*)ft_memalloc(sizeof(struct fat_arch));
	if (arch== NULL)
		return (NULL);
	offset = sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
	ft_memcpy(arch, file + offset, sizeof(struct fat_arch));
	if ((flags & IS_SWAPPED))
	{
		arch->cputype = OSSwapInt32(arch->cputype);
		arch->cpusubtype = OSSwapInt32(arch->cputype);
		arch->offset = OSSwapInt32(arch->offset);
		arch->size = OSSwapInt32(arch->size);
		arch->align = OSSwapInt32(arch->align);
	}
	return (arch);
}

/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
*/

int		dump_fat_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	uint32_t			i;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	i = 0;
	fat = extract_fat_header(file, ctx->flags);
	while (i < fat->nfat_arch)
	{
		arch = extract_fat_arch(file, ctx->flags, i);
		if (arch->cputype == CPU_TYPE_X86_64 && HOST_64BIT)
			dump_macho64_bin(file + arch->offset, ctx, dump);
		free(arch);
		i += 1;
	}
	free(fat);
	return (EXIT_SUCCESS);
}

/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
*/

int		dump_fat64_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	(void)file;
	(void)ctx;
	(void)dump;
	return (EXIT_SUCCESS);
}

