/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:55 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/14 01:06:17 by tmatthew         ###   ########.fr       */
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
		if ((file + archs[i].offset < file + (i * sizeof(struct fat_arch)))
			|| (file + archs[i].offset + archs[i].size > file + ctx->size)
			|| ((align = uint32_pow(2, archs[i].align)) == UINT32_MAX)
			|| (((uint32_t)file + archs[i].offset) % align)
			|| (validate_file(file + archs[i].offset, ctx, TRUE) == EXIT_FAILURE))
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
