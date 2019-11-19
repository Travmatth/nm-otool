/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/18 18:18:42 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

int		print_text(t_ctx *ctx, struct segment_command *segment)
{
	(void)ctx;
	(void)segment;
	return (EXIT_SUCCESS);
}

int		print_text64(t_ctx *ctx, struct segment_command_64 *segment)
{
	(void)ctx;
	(void)segment;
	return (EXIT_SUCCESS);
}
