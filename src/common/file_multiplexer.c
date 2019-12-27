/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_multiplexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:22:21 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/26 15:33:36 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		file_multiplexer(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	int		flags;

	flags = ctx->flags;
	ctx->flags = 0;
	if (determine_file(file, ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if ((ctx->flags & IS_FAT)
		&& dump_fat_bin(file, ctx, dump) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if ((ctx->flags & IS_32)
		&& dump_macho_bin(file, ctx, dump) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (dump_macho64_bin(file, ctx, dump) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ctx->flags = flags;
	return (EXIT_SUCCESS);
}
