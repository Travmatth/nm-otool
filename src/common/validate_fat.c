/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:55 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/14 00:09:17 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

int		validate_fat(char *file, t_ctx *ctx)
{
	uint32_t			i;
	uint32_t			align;
	int					status;
	struct fat_header	header;
	struct fat_arch		*archs;

	i = 0;
	status = EXIT_SUCCESS;
	header = *(struct fat_header*)file;
	if (ctx->flags & SWAP)
		swap_fat_header(&header, NX_UnknownByteOrder);
	if ((archs = ft_memdup(file + sizeof(struct fat_header)
		, sizeof(struct fat_arch) * header.nfat_arch)) == NULL)
		return (EXIT_FAILURE);
	if (ctx->flags & SWAP)
		swap_fat_arch(archs, header.nfat_arch, NX_UnknownByteOrder);
	while (status == EXIT_SUCCESS && i < header.nfat_arch)
	{
		if (file + archs[i].offset < file + (i * sizeof(struct fat_arch)))
			status = EXIT_FAILURE;
		else if (file + archs[i].offset + archs[i].size > file + ctx->size)
			status = EXIT_FAILURE;
		else if ((align = uint32_pow(2, archs[i].align)) == UINT32_MAX)
			status = EXIT_FAILURE;
		else if (((uint32_t)file + archs[i].offset) % align)
			status = EXIT_FAILURE;
		else if (validate_file(file + archs[i].offset, ctx, TRUE) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		i += 1;
	}
	return (status);
}

// int		validate_fat_object(char *file, t_ctx *ctx, uint32_t i, uint32_t arch_offset)
// {
// 	struct fat_arch	*arch;
// 	uint32_t		align;
// 	uint32_t		offset;

// 	arch = (struct fat_arch*)(file + arch_offset);
// 	offset = (ctx->flags & SWAP) ? OSSwapInt32(arch->offset) : arch->offset;
// 	if (file + offset < file + (i * sizeof(struct fat_arch)))
// 		return (EXIT_FAILURE);
// 	else if (file + offset + swap(ctx, arch->size) > file + ctx->size)
// 		return (EXIT_FAILURE);
// 	else if ((align = uint32_pow(2, swap(ctx, arch->align))) == UINT32_MAX)
// 		return (EXIT_FAILURE);
// 	else if (((uint32_t)file + offset) % align)
// 		return (EXIT_FAILURE);
// 	else if (validate_file(file + offset, ctx, TRUE) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// int		validate_fat(char *file, t_ctx *ctx)
// {
// 	uint32_t			i;
// 	uint32_t			offset;
// 	struct fat_header	header;

// 	i = 0;
// 	offset = sizeof(struct fat_header);
// 	header = (struct fat_header*)file;
// 	if (ctx->flags & SWAP)
// 		swap_fat_header(&header, NX_UnknownByteOrder);
// 	archs = swap(ctx, ()->nfat_arch);
// 	while (i < archs)
// 	{
// 		offset += sizeof(struct fat_arch);
// 		if (validate_fat_object(file, ctx, i, offset) == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 		i += 1;
// 	}
// 	return (EXIT_SUCCESS);
// }
