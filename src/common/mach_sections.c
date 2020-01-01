/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_sections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:39:14 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/31 19:51:27 by tmatthew         ###   ########.fr       */
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

int		dump_sects(char *file, struct segment_command *segment, t_dump_fxs *dump)
{
	uint32_t		i;
	uint32_t		offset;
	struct section	*section;
	void			*addr;

	i = 0;
	offset = ((char*)segment - file) + sizeof(struct segment_command);
	while (i < segment->nsects)
	{
		section = (struct section*)(file + offset);
		addr = file + section->offset;
		if (dump->section && !OK(dump->section(file, section, NULL)))
				return (EXIT_FAILURE);
		offset += sizeof(struct section);
		i += 1;
	}
	return (EXIT_SUCCESS);
}


/*
** iterate over 64bit sections and with callback function
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command_64} current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @param{ptrdiff_t} offset of section within binary file
** @return {int} 0 on success, 1 on failure
*/

int		dump_sects_64(char *file, struct segment_command_64 *segment, t_dump_fxs *dump)
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
		if (dump->section && !OK(dump->section(file, NULL, section)))
				return (EXIT_FAILURE);
		offset += sizeof(struct section_64);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
