/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_multiplexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:22:21 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/31 20:59:59 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		file_multiplexer(char *file, t_ctx *ctx, t_dump_fxs *dump, int validate)
{
	int		flags;

	flags = ctx->flags;
	ctx->flags = 0;
	if (!OK(determine_file(file, ctx)))
		return (EXIT_FAILURE);
	else if (validate && !OK(validate_file(file, ctx)))
		return (EXIT_FAILURE);
	ft_putstr_fd(ctx->filename, STDOUT_FILENO);
	ft_putendl_fd(":", STDOUT_FILENO);
	if ((ctx->flags & IS_FAT) && !OK(dump_fat_bin(file, ctx, dump)))
		return (EXIT_FAILURE);
	else if ((ctx->flags & IS_32) && !OK(dump_macho_bin(file, ctx, dump)))
		return (EXIT_FAILURE);
	else if ((ctx->flags & IS_64) && !OK(dump_macho64_bin(file, ctx, dump)))
		return (EXIT_FAILURE);
	ctx->flags = flags;
	return (EXIT_SUCCESS);
}
