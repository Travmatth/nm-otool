/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:11:40 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 15:52:23 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		prep_x86_64_section(t_x86_64_text *x86_64_text, int *i)
{
	int		len;
	struct section_64	**new_sections;
	char				**new_data;
	int					*new_flags;

	*i = 0;
	while (x86_64_text->sections && x86_64_text->sections[*i])
		*i += 1;
	len = *i + 2;
	if ((new_sections = ft_memalloc(sizeof(struct section_64*) * len)) == NULL)
		return (EXIT_SUCCESS);
	else if ((new_data = ft_memalloc(sizeof(char*) * len)) == NULL)
		return (EXIT_SUCCESS);
	else if ((new_flags = ft_memalloc(sizeof(int) * len)) == NULL)
		return (EXIT_SUCCESS);
	if (*i != 0)
	{
		ft_memcpy(new_sections, x86_64_text->sections, sizeof(struct section_64*) * *i);
		ft_memcpy(new_data, x86_64_text->data, sizeof(char*) * *i);
		ft_memcpy(new_flags, x86_64_text->flags, sizeof(int) * *i);
	}
	x86_64_text->sections = new_sections;
	x86_64_text->data = new_data;
	x86_64_text->flags = new_flags;
	return (EXIT_SUCCESS);
}

/*
** Save sections of the input file for later printing
*/

int		save_x86_64_section(struct section_64 *sect, t_ctx *ctx, int flags)
{
	int		i;

	if (sect == NULL)
		return (EXIT_SUCCESS);
	if ((ctx->targets & TEXT_SECTIONS) && ft_strcmp(SECT_TEXT, sect->sectname))
	{
		if (prep_x86_64_section(&ctx->out.x86_64_text, &i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((ctx->out.x86_64_text.sections[i] = ft_memdup(sect, sizeof(struct section_64))) == NULL)
			return (EXIT_FAILURE);
		ctx->out.x86_64_text.flags[i] = flags;
		ctx->out.x86_64_text.data[i] = ctx->file + sect->offset;
	}
	return (EXIT_SUCCESS);
}

/*
**
*/

int		prep_i386_section(t_i386_text *i386, int *i)
{
	int				len;
	struct section	**new_sections;
	char			**new_data;
	int				*new_flags;

	*i = 0;
	while (i386->sections && i386->sections[*i])
		*i += 1;
	len = *i + 2;
	if ((new_sections = ft_memalloc(sizeof(struct section*) * len)) == NULL)
		return (EXIT_SUCCESS);
	else if ((new_data = ft_memalloc(sizeof(char*) * len)) == NULL)
		return (EXIT_SUCCESS);
	else if ((new_flags = ft_memalloc(sizeof(int) * len)) == NULL)
		return (EXIT_SUCCESS);
	if (*i != 0)
	{
		ft_memcpy(new_sections, i386->sections, sizeof(struct section*) * *i);
		ft_memcpy(new_data, i386->data, sizeof(char*) * *i);
		ft_memcpy(new_flags, i386->flags, sizeof(int) * *i);
	}
	i386->sections = new_sections;
	i386->data = new_data;
	i386->flags = new_flags;
	return (EXIT_SUCCESS);
}

/*
** Save sections of the input file for later printing
*/

int		save_i386_section(struct section *sect, t_ctx *ctx, int flags)
{
	int		i;

	if (sect == NULL)
		return (EXIT_SUCCESS);
	if ((ctx->targets & TEXT_SECTIONS) && ft_strcmp(SECT_TEXT, sect->sectname))
	{
		if (prep_i386_section(&ctx->out.i386_text, &i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((ctx->out.i386_text.sections[i] = ft_memdup(sect, sizeof(struct section))) == NULL)
			return (EXIT_FAILURE);
		ctx->out.i386_text.flags[i] = flags;
		ctx->out.i386_text.data[i] = ctx->file + sect->offset;
	}
	return (EXIT_SUCCESS);
}

int		save_i386_header(struct mach_header *header, t_ctx *ctx, int flags)
{
	(void)header;
	(void)ctx;
	(void)flags;
	return (EXIT_SUCCESS);
}

int		save_x86_64_header(struct mach_header_64 *header, t_ctx *ctx, int flags)
{
	(void)header;
	(void)ctx;
	(void)flags;
	return (EXIT_SUCCESS);
}

int		save_i386_segment(struct segment_command *segment, t_ctx *ctx, int flags)
{
	(void)segment;
	(void)ctx;
	(void)flags;
	return (EXIT_SUCCESS);
}

int		save_x86_64_segment(struct segment_command_64 *segment, t_ctx *ctx, int flags)
{
	(void)segment;
	(void)ctx;
	(void)flags;
	return (EXIT_SUCCESS);
}
