/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_multiplexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:22:21 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/13 23:33:48 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		file_multiplexer(char *file, t_ctx *ctx, t_dump_fxs *dump, int validate)
{
	int		f;
	int		flags;
	int		status;

	flags = ctx->flags;
	ctx->flags = 0;
	status = EXIT_SUCCESS;
	if (validate == TRUE && !OK(validate_file(file, ctx, FALSE)))
	{
		ctx->flags = flags;
		return (EXIT_FAILURE);
	}
	else if (validate == FALSE)
		determine_file(file, ctx);
	f = ctx->flags;
	if ((f & IS_FAT))
		status = dump_fat_bin(file, ctx, dump);
	else if ((f & IS_32) && (f & IS_MACH))
		status = dump_mach_i386(file, ctx, dump);
	else if ((f & IS_64) && (f & IS_MACH) && !(f & SWAP))
		status = dump_mach_x86_64(file, ctx, dump);
	else if ((f & IS_64) && (f & IS_MACH) && (f & SWAP))
		status = EXIT_SUCCESS;
	ctx->flags = flags;
	return (status);
}
