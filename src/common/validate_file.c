/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:19:02 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/13 23:38:45 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

int		validate_file(char *file, t_ctx *ctx, int classify)
{
	int		f;
	int		flags;
	int		status;

	if (classify == TRUE)
	{
		flags = ctx->flags;
		ctx->flags = 0;
	}
	determine_file(file, ctx);
	ctx->objects += 1;
	f = ctx->flags;
	status = EXIT_FAILURE;
	if (f & IS_FAT)
		status = validate_fat(file, ctx);
	else if ((f & IS_MACH) && (f & IS_64) && !(f & SWAP))
		status = validate_mach_x86_64(file, ctx);
	else if ((f & IS_MACH) && (f & IS_32))
		status = validate_mach_i386(file, ctx);
	else if ((f & IS_MACH) && (f & IS_64) && (f & SWAP))
		status = EXIT_SUCCESS;
	if (classify == TRUE)
		ctx->flags = flags;
	return (status);
}
