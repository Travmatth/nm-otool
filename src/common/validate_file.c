/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:19:02 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/10 21:31:30 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** determine if given file is FAT, 32/64bit Mach-O binary, or archive
** @param {t_ctx*} struct containing file
** @return {int} 0 on success, 1 on error
*/

int			determine_magic(char *file, int *flags)
{
	uint32_t	magic;

	magic = *(uint32_t*)file;
	if (is_fat32(flags, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_fat64(flags, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_mach32(flags, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_mach64(flags, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (is_archive(file, flags));
}

int		validate_file(char *file, t_ctx *ctx, int flags)
{
	int		status;

	ctx->objects += 1;
	status = EXIT_FAILURE;
	if (flags & IS_FAT)
		status = validate_fat(file, ctx, flags);
	else if ((flags & IS_MACH) && (flags & IS_64) && !(flags & SWAP))
		status = validate_mach_x86_64(file, ctx, flags);
	else if ((flags & IS_MACH) && (flags & IS_32))
		status = validate_mach_i386(file, ctx, flags);
	else if ((flags & IS_MACH) && (flags & IS_64) && (flags & SWAP))
		status = EXIT_SUCCESS;
	else if ((flags & IS_EXTENDED_ARCHIVE))
		status = validate_extended_archive(file, ctx);
	return (status);
}

int		validate_file_flags(char *file, t_ctx *ctx, int *flags)
{
	determine_magic(file, flags);
	return (validate_file(file, ctx, *flags));
}

int		validate_unknown(char *file, t_ctx *ctx)
{
	int		flags;

	flags = 0;
	return (validate_file_flags(file, ctx, &flags));
}
