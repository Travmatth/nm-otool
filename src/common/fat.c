/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/28 23:55:56 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
*/

int		dump_fat_bin(t_ctx *ctx, t_dump_funcs *funcs)
{
	(void)ctx;
	(void)funcs;
	return (EXIT_SUCCESS);
}
