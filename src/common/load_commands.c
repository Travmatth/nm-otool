/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:48:05 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/10 21:47:17 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		dump_load_command(char *file, t_ctx *ctx, t_dump_fxs *dump, int flags, t_lcommand *u)
{
	int					status;
	struct load_command	load;

	load = *u->load;
	status = EXIT_SUCCESS;
	if (flags & SWAP)
		swap_load_command(&load, NX_UnknownByteOrder);
	if (dump->load && !OK(dump->load(file, ctx, NULL, u)))
		return (EXIT_FAILURE);
	if (load.cmd == LC_SEGMENT && dump->i386_segment)
		status = dump->i386_segment(file, ctx, flags, u->segment);
	if (load.cmd == LC_SEGMENT && status == EXIT_SUCCESS)
		status = dump_i386_sections(file, u->segment, dump, flags);
	if (load.cmd == LC_SEGMENT_64 && dump->x86_64_segment)
		status = dump->x86_64_segment(file, ctx, flags, u->segment64);
	if (load.cmd == LC_SEGMENT_64 && status == EXIT_SUCCESS)
		status = dump_x86_64_sections(file, u->segment64, dump);
	return (status);
}
