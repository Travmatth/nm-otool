/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_x86_64_sections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:39:14 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/05 17:32:47 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over 32bit sections and with callback function
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command} current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @param{ptrdiff_t} offset of section within binary file
** @return {int} 0 on success, 1 on failure
*/

int		dump_i386_sections(char *file, struct segment_command *segment, t_dump_fxs *dump, int flags)
{
	uint32_t		nsects;
	uint32_t		offset;
	struct section	*section;
	void			*addr;

	nsects = flags & SWAP ? OSSwapInt32(segment->nsects) : segment->nsects;
	offset = ((char*)segment - file) + sizeof(struct segment_command);
	while (nsects--)
	{
		section = (struct section*)(file + offset);
		addr = file + (flags & SWAP ? OSSwapInt32(section->offset) : section->offset);
		if (dump->i386_section && !OK(dump->i386_section(file, flags & SWAP, section)))
				return (EXIT_FAILURE);
		offset += sizeof(struct section);
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

int		dump_mach_i386(char *file, t_ctx *ctx, t_dump_fxs *dump, int flags)
{
	t_lcommand			u;
	struct mach_header	*hdr;
	uint64_t			ncmds;
	uint64_t			offset;

	hdr = (struct mach_header*)file;
	ncmds = (flags & SWAP) ? OSSwapInt32(hdr->ncmds) : hdr->ncmds;
	offset = sizeof(struct mach_header);
	if (dump->header && !OK(dump->header(file, ctx, hdr, NULL)))
		return (EXIT_FAILURE);
	print_section_prologue(file, ctx);
	while (ncmds--)
	{
		if ((u.load = (struct load_command*)(file + offset)) && flags & SWAP)
			swap_load_command(u.load, NX_UnknownByteOrder);
		if (u.load->cmd == LC_SEGMENT && dump->segment &&
			((!OK(dump->segment(file, ctx, u.segment, NULL)))
				|| (!OK(dump_i386_sections(file, u.segment, dump, flags)))))
			return (EXIT_FAILURE);
		if (dump->load && !OK(dump->load(file, ctx, NULL, u.load)))
			return (EXIT_FAILURE);
		offset += u.load->cmdsize;
	}
	return (EXIT_SUCCESS);
}
