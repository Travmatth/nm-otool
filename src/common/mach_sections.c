/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_sections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:39:14 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/15 19:51:51 by tmatthew         ###   ########.fr       */
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

int		dump_sects(char *file, t_ctx *ctx, t_macho32 *mach, t_dump_fxs *dump)
{
	uint32_t		i;
	uint32_t		offset;
	struct section	*section;
	void			*addr;

	i = 0;
	offset = mach->offset + sizeof(struct segment_command);
	while (i < mach->sc->nsects)
	{
		section = (struct section*)(ctx->file + offset);
		addr = ctx->file + section->offset;
		if (dump->section && !OK(dump->section(file, ctx, section, NULL)))
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

int		dump_sects_64(char *file, t_ctx *ctx, t_macho64 *mach, t_dump_fxs *dump)
{
	uint64_t			i;
	uint64_t			offset;
	struct section_64	*section;
	void				*addr;

	i = 0;
	offset = mach->offset + sizeof(struct segment_command_64);
	while (i < mach->sc->nsects)
	{
		section = (struct section_64*)(file + offset);
		addr = file + section->offset;
		if (dump->section && !OK(dump->section(file, ctx, NULL, section)))
				return (EXIT_FAILURE);
		offset += sizeof(struct section_64);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
