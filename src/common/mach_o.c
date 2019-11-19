/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:40 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/18 18:46:38 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_func} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
*/

int		dump_mach_segs(t_ctx *ctx, t_seg_func f, t_seg64_func f64)
{
	(void)ctx;
	(void)f;
	(void)f64;
	return (EXIT_SUCCESS);
}
