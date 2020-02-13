/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_multiplexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:22:21 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/12 09:10:01 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		file_multiplexer(char *file, t_ctx *ctx, t_dump_fxs *dump, int flags)
{
	int		status;

	status = EXIT_SUCCESS;
	if ((flags & IS_FAT))
		status = dump_fat_bin(file, ctx, dump);
	else if ((flags & IS_32) && (flags & IS_MACH))
		status = dump_mach_i386(file, ctx, dump, flags);
	else if ((flags & IS_64) && (flags & IS_MACH) && !(flags & SWAP))
		status = dump_mach_x86_64(file, ctx, dump, flags);
	else if ((flags & IS_64) && (flags & IS_MACH) && (flags & SWAP))
		status = EXIT_SUCCESS;
	return (status);
}

int		validate_multiplex(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	int		flags;
	int		status;

	flags = 0;
	status = EXIT_SUCCESS;
	if (validate_file_flags(file, ctx, &flags) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (file_multiplexer(file, ctx, dump, flags));
}
