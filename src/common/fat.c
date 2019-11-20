/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/20 13:10:50 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_func} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
*/

int		dump_fat_lcmds(t_ctx *ctx, t_seg_func f, t_seg64_func f64)
{
	(void)ctx;
	(void)f;
	(void)f64;
	return (EXIT_SUCCESS);
}
