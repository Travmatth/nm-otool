/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_load_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:13:03 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 22:44:16 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

int		validate_load_command(t_header *h, t_ctx *ctx, int flags, t_lcommand *u)
{
	int					status;
	struct load_command	load;
	t_hook				hook;

	if (flags & SWAP)
		swap_load_command(&u->load, NX_UnknownByteOrder);
	if (u->load.cmdsize % 4)
		return (EXIT_FAILURE);
	hook = ctx->hook;
	status = EXIT_SUCCESS;
	if (u->load.cmd == LC_SEGMENT)
		status = validate_i386_segment(&u->segment, ctx, , flags);
	else if (u->load.cmd == LC_SEGMENT_64 && status == EXIT_SUCCESS)
		status = x86_64_sections(&u->segment64, hook);
	else if (u->load.cmd == LC_SYMTAB && flags & IS_32)
		status = validate_symtab_i386(&h->header, ctx, &u->symtab, flags);
	else if (u->load.cmd == LC_SYMTAB && flags & IS_64)
		status = validate_symtab_x86_64(&h->header_64, ctx, &u->symtab, flags);
	ctx->offset += load.cmdsize;
	return (status);
}
