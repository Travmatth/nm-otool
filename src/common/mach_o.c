/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:40 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/27 22:25:39 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over sections and with callback function
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment} current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @param{ptrdiff_t} offset
*/

int		dump_sections(t_ctx *ctx
					, struct segment_command *sc
					, t_dump_funcs *funcs
					, ptrdiff_t offset)
{
	uint32_t		i;
	struct section	*section;

	i = 0;
	offset += sizeof(struct segment_command);
	while (i < sc->nsects)
	{
		section = (struct section*)(ctx->file + offset);
		if (funcs->section)
			funcs->section(ctx, section, NULL, NULL);
		offset += sizeof(struct section);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

/*
** iterate over 32bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
*/

int		dump_mach_lcmds(t_ctx *ctx, t_dump_funcs *funcs)
{
	ptrdiff_t				offset;
	uint32_t				num_commands;
	struct mach_header		*hdr;
	struct load_command		*lc;
	struct segment_command	*sc;

	hdr = (struct mach_header *)ctx->file;
	num_commands = hdr->ncmds;
	offset = sizeof(struct mach_header);
	while (num_commands-- && (lc = (struct load_command *)(ctx->file + offset)))
	{
		if (lc->cmd != LC_SEGMENT)
		{
			if (funcs->load && (funcs->load(ctx, lc, NULL) == EXIT_FAILURE))
				return (EXIT_FAILURE);
			offset += lc->cmdsize;
			continue;
		}
		sc = (struct segment_command*)(ctx->file + offset);
		if ((dump_sections(ctx, sc, funcs, offset) == EXIT_FAILURE)
			|| (funcs->segment && funcs->segment(
				ctx, sc, NULL, SEG_POS(ctx, hdr, sc)) == EXIT_FAILURE))
			return (EXIT_FAILURE);
		offset += sc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

/*
** iterate over 64bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
*/

int		dump_mach_lcmds64(t_ctx *ctx, t_dump_funcs *funcs)
{
	(void)ctx;
	(void)funcs;
	return (EXIT_SUCCESS);
}
