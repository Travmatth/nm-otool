/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/27 20:44:30 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** determine if given section is __TEXT,__text and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct section*} section to print
** @param{struct section_64*} section to print
*/

int		print_text(t_ctx *ctx
					, struct section *section
					, struct section_64 *section_64)
{
	(void)ctx;
	(void)section;
	(void)section_64;
	return (EXIT_SUCCESS);
}
