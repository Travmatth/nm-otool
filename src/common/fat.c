/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/26 15:22:41 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** extract FAT head from FAT binary, swap endianness if needed
** @param{file*} binary file being parsed
** @param{flags*} opts used to determine endianness
** @return {struct fat_header} fat_header on success, NULL on failure
*/

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

/*
** extract FAT arch struct from FAT 32bit binary, swap endianness if needed
** @param{file*} binary file being parsed
** @param{t_ctx*} program context
** @param{struct fat_arch**} pointer to store fat_arch
** @return {int} 0 on success, 1 on failure
*/

int		extract_fat_arch(char *file, int flags, struct fat_arch	**arch)
{
	*arch = (struct fat_arch*)ft_memalloc(sizeof(struct fat_arch));
	if (arch== NULL)
		return (EXIT_FAILURE);
	ft_memcpy(*arch, file, sizeof(struct fat_arch));
	if ((flags & IS_SWAPPED))
	{
		(*arch)->cputype = OSSwapInt32((*arch)->cputype);
		(*arch)->cpusubtype = OSSwapInt32((*arch)->cputype);
		(*arch)->offset = OSSwapInt32((*arch)->offset);
		(*arch)->size = OSSwapInt32((*arch)->size);
		(*arch)->align = OSSwapInt32((*arch)->align);
	}
	return (EXIT_SUCCESS);
}

/*
** extract FAT arch struct from FAT 64bit binary, swap endianness if needed
** @param{file*} binary file being parsed
** @param{t_ctx*} program context
** @param{struct fat_arch_64**} pointer to store fat_arch
** @return {int} 0 on success, 1 on failure
*/

int		extract_fat_arch_64(char *file, int flags, struct fat_arch_64 **arch)
{
	*arch = (struct fat_arch_64*)ft_memalloc(sizeof(struct fat_arch_64));
	if (arch== NULL)
		return (EXIT_FAILURE);
	ft_memcpy(*arch, file, sizeof(struct fat_arch_64));
	if ((flags & IS_SWAPPED))
	{
		(*arch)->cputype = OSSwapInt32((*arch)->cputype);
		(*arch)->cpusubtype = OSSwapInt32((*arch)->cputype);
		(*arch)->offset = OSSwapInt32((*arch)->offset);
		(*arch)->size = OSSwapInt32((*arch)->size);
		(*arch)->align = OSSwapInt32((*arch)->align);
	}
	return (EXIT_SUCCESS);
}

/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_fat_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	uint32_t			i;
	uint32_t			offset;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	i = 0;
	if (!(fat = extract_fat_header(file, ctx->flags)))
		return (EXIT_FAILURE);
	while (i < fat->nfat_arch)
	{
		offset = sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
		if (!OK(extract_fat_arch(file + offset, ctx->flags, &arch)))
			return (EXIT_FAILURE);
		if (arch->cputype == CPU_TYPE_X86_64 && HOST_64BIT)
			file_multiplexer(file + arch->offset, ctx, dump);
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
** @return {int} 0 on success, 1 on failure
*/

int		dump_fat64_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	uint32_t				i;
	uint32_t				offset;
	struct fat_header		*fat;
	struct fat_arch_64		*arch;

	i = 0;
	if (!(fat = extract_fat_header(file, ctx->flags)))
		return (EXIT_FAILURE);
	while (i < fat->nfat_arch)
	{
		offset = sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
		if (!OK(extract_fat_arch_64(file + offset, ctx->flags, &arch)))
			return (EXIT_FAILURE);
		if (arch->cputype == CPU_TYPE_X86_64 && HOST_64BIT)
			file_multiplexer(file + arch->offset, ctx, dump);
		free(arch);
		i += 1;
	}
	free(fat);
	return (EXIT_SUCCESS);
}

