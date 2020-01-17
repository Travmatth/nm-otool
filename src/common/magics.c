/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:35:51 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/15 15:50:39 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** determine if given file is binary formatted with 32bit FAT syntax
** @param {t_ctx*} program context containing binary file being parsed
** @param {uint32_t} magic number of given file
** @return {int} 0 on success, 1 on error
*/

int		is_fat32(t_ctx *ctx, uint32_t magic)
{
	if (magic == FAT_MAGIC)
	{
		ctx->flags |= IS_32;
		ctx->flags |= IS_FAT;
	}
	else if (magic == FAT_CIGAM)
	{
		ctx->flags |= IS_32;
		ctx->flags |= IS_FAT;
		ctx->flags |= SWAP;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** determine if given file is binary formatted with 64bit FAT syntax
** @param {t_ctx*} program context containing binary file being parsed
** @param {uint32_t} magic number of given file
** @return {int} 0 on success, 1 on error
*/

int		is_fat64(t_ctx *ctx, uint32_t magic)
{
	if (magic == FAT_MAGIC_64)
		ctx->flags |= IS_FAT;
	else if (magic == FAT_CIGAM_64)
	{
		ctx->flags |= IS_FAT;
		ctx->flags |= SWAP;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** determine if given file is binary formatted with 64bit Mach-O syntax
** @param {t_ctx*} program context containing binary file being parsed
** @param {uint32_t} magic number of given file
** @return {int} 0 on success, 1 on error
*/

int		is_mach64(t_ctx *ctx, uint32_t magic)
{
	if (magic == MH_CIGAM_64)
	{
		ctx->flags |= IS_64;
		ctx->flags |= SWAP;
		ctx->flags |= IS_MACH;
		return (EXIT_SUCCESS);
	}
	else if (magic == MH_MAGIC_64)
	{
		ctx->flags |= IS_MACH;
		ctx->flags |= IS_64;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** determine if given file is binary formatted with 32bit Mach-O syntax
** @param {t_ctx*} program context containing binary file being parsed
** @param {uint32_t} magic number of given file
** @return {int} 0 on success, 1 on error
*/

int		is_mach32(t_ctx *ctx, uint32_t magic)
{
	if (magic == MH_MAGIC)
	{
		ctx->flags |= IS_32;
		ctx->flags |= IS_MACH;
	}
	else if (magic == MH_CIGAM)
	{
		ctx->flags |= IS_32;
		ctx->flags |= SWAP;
		ctx->flags |= IS_MACH;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** determine if given file is linux or mac extended archive
** @param {t_ctx*} program context containing binary file being parsed
** @param {uint32_t} magic number of given file
** @return {int} 0 on success, 1 on error
*/

int		is_archive(char *file, t_ctx *ctx)
{
	char	name[SARMAG + 4];

	ft_strcpy(name, ARMAG);
	ft_strcat(name, AR_EFMT1);
	if (ctx->size >= SARMAG + 2 && !ft_strncmp(name, file, SARMAG + 2))
		ctx->flags |= IS_EXTENDED_ARCHIVE;
	else if (ctx->size >= SARMAG && !ft_strncmp(name, file, SARMAG))
		ctx->flags |= IS_ARCHIVE;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
