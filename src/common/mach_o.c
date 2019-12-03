/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:40 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/02 21:37:33 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over sections and with callback function
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment} current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @param{ptrdiff_t} offset of section within binary file
** @return {int} 0 on success, 1 on failure
*/

int		dump_sections(t_ctx *ctx
					, struct segment_command *sc
					, t_dump_fxs *fxs
					, ptrdiff_t offset)
{
	uint32_t		i;
	struct section	*section;
	void			*addr;

	i = 0;
	offset += sizeof(struct segment_command);
	while (i < sc->nsects)
	{
		section = (struct section*)(ctx->file + offset);
		addr = ctx->file + section->offset;
		if (fxs->section && fxs->section(ctx, section, NULL) == EXIT_FAILURE)
				return (EXIT_FAILURE);
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
** @return {int} 0 on success, 1 on failure
*/

int		dump_macho_bin(t_ctx *ctx, t_dump_fxs *fxs)
{
	t_mach_o_32	mach;

	mach.hdr = (struct mach_header *)ctx->file;
	mach.num_commands = mach.hdr->ncmds;
	mach.offset = sizeof(struct mach_header);
	if (fxs->header && (fxs->header(ctx, mach.hdr, NULL) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	while (mach.num_commands-- &&
		(mach.lc = (struct load_command *)(ctx->file + mach.offset)))
	{
		if (mach.lc->cmd != LC_SEGMENT)
		{
			if (fxs->load && (fxs->load(ctx, mach.lc, NULL) == EXIT_FAILURE))
				return (EXIT_FAILURE);
			mach.offset += mach.lc->cmdsize;
			continue;
		}
		mach.sc = (struct segment_command*)(ctx->file + mach.offset);
		if ((fxs->segment && fxs->segment(ctx, mach.sc, NULL) == EXIT_FAILURE)
			|| (dump_sections(ctx, mach.sc, fxs, mach.offset) == EXIT_FAILURE))
			return (EXIT_FAILURE);
		mach.offset += mach.sc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

/*
** iterate over 64bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_macho_bin64(t_ctx *ctx, t_dump_fxs *fxs)
{
	(void)ctx;
	(void)fxs;
	return (EXIT_SUCCESS);
}
