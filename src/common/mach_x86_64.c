/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_x86_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:58:40 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/10 15:16:54 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** iterate over 64bit sections and with callback function
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command_64} current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @param{ptrdiff_t} offset of section within binary file
** @return {int} 0 on success, 1 on failure
*/

int		dump_x86_64_sections(char *file, struct segment_command_64 *segment, t_dump_fxs *dump)
{
	uint64_t			i;
	uint64_t			offset;
	struct section_64	*section;
	void				*addr;

	i = 0;
	offset = ((char*)segment - file) + sizeof(struct segment_command_64);
	while (i < segment->nsects)
	{
		section = (struct section_64*)(file + offset);
		addr = file + section->offset;
		if (dump->x86_64_section && !OK(dump->x86_64_section(file, section)))
				return (EXIT_FAILURE);
		offset += sizeof(struct section_64);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

/*
** iterate over 64bit mach-o binary and parse each segment
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_mach_x86_64(char *file, t_ctx *ctx, t_dump_fxs *dump, int flags)
{
	struct mach_header_64	*hdr;
	t_lcommand				u;
	uint64_t				i;
	uint64_t				offset;

	i = 0;
	hdr = (struct mach_header_64*)file;
	offset = sizeof(struct mach_header_64);
	if (dump->x86_64_header && !OK(dump->x86_64_header(file, hdr)))
		return (EXIT_FAILURE);
	print_section_prologue(file, ctx);
	while (i++ < hdr->ncmds)
	{
		u.load = (struct load_command*)(file + offset);
		if (dump_load_command(file, ctx, dump, flags, &u) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		offset += u.load->cmdsize;
	}
	return (EXIT_SUCCESS);
}
