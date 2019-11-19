/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/18 18:49:23 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** determine if given section is __TEXT,__text and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command*} segment to print
*/

int		print_section(t_ctx *ctx, struct segment_command *segment)
{
	(void)ctx;
	(void)segment;
	return (EXIT_SUCCESS);
}

/*
** determine if given 64bit section is __TEXT,__text and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command*} segment to print
*/

int		print_section64(t_ctx *ctx, struct segment_command_64 *segment)
{
	(void)ctx;
	(void)segment;
	return (EXIT_SUCCESS);
}
