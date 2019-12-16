/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:40 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/15 22:09:00 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** extract header from 32 & 64 bit mach-o binary files
** @param{char*} binary file being parsed
** @param{t_macho32} struct to file with binary's options
** @param{t_macho64} struct to file with binary's options
** @return {void}
*/

void	extract_mach_header(char *file, t_macho32 *mach32, t_macho64 *mach64)
{
	if (mach32)
	{
		mach32->hdr = (struct mach_header *)ft_memalloc(sizeof(struct mach_header));
		ft_memcpy(mach32->hdr, file, sizeof(struct mach_header));
		mach32->num_commands = mach32->hdr->ncmds;
		mach32->offset = sizeof(struct mach_header);
	}
	else if (mach64)
	{
		mach64->hdr = (struct mach_header_64 *)ft_memalloc(sizeof(struct mach_header_64));
		ft_memcpy(mach64->hdr, file, sizeof(struct mach_header_64));
		mach64->num_commands = mach64->hdr->ncmds;
		mach64->offset = sizeof(struct mach_header_64);
	}
}

/*
** iterate over 32bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_seg64_func} function called with current segment being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_macho_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	t_macho32	mach;

	extract_mach_header(file, &mach, NULL);
	if (dump->header && !OK(dump->header(file, ctx, mach.hdr, NULL)))
		return (EXIT_FAILURE);
	while (mach.num_commands-- &&
		(mach.lc = (struct load_command *)(file + mach.offset)))
	{
		if (mach.lc->cmd != LC_SEGMENT)
		{
			if (dump->load && !OK(dump->load(file, ctx, mach.lc, NULL)))
				return (EXIT_FAILURE);
			mach.offset += mach.lc->cmdsize;
			continue;
		}
		mach.sc = (struct segment_command*)(file + mach.offset);
		if ((dump->segment && !OK(dump->segment(file, ctx, mach.sc, NULL)))
			|| !OK(dump_sects(file, ctx, &mach, dump)))
			return (EXIT_FAILURE);
		mach.offset += mach.sc->cmdsize;
	}
	free(mach.hdr);
	return (EXIT_SUCCESS);
}

/*
** iterate over 64bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_macho64_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	t_macho64	mach;

	extract_mach_header(file, NULL, &mach);
	if (dump->header && !OK(dump->header(file, ctx, NULL, mach.hdr)))
		return (EXIT_FAILURE);
	while (mach.num_commands-- &&
		(mach.lc = (struct load_command*)(file + mach.offset)))
	{
		if (mach.lc->cmd == LC_SEGMENT_64)
		{
			mach.sc = (struct segment_command_64*)(file + mach.offset);
			if ((dump->segment && !OK(dump->segment(file, ctx, NULL, mach.sc)))
				|| (!OK(dump_sects_64(file, ctx, &mach, dump))))
				return (EXIT_FAILURE);
			mach.offset += mach.sc->cmdsize;
			continue;
		}
		if (dump->load && !OK(dump->load(file, ctx, NULL, mach.lc)))
			return (EXIT_FAILURE);
		mach.offset += mach.lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
