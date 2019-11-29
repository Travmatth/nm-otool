/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/29 00:25:26 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** print __text section contents in 16 byte rows prefixed with pointer address
** @param{t_sect} info on section to print
** @return {int} 0 on success, 1 on failure
*/

int		print_text_contents(t_sect *fmt)
{
	uint32_t	current;
	char		ptr_buf[17];
	char		mem_buf[24];

	current = 0;
	while (current < fmt->size)
	{
		if (current % 16)
		{
			format_pointer(fmt->addr, ptr_buf, fmt->is_64);
			ft_printf("%s        ", ptr_buf);
		}
		while (current < fmt->size && current % 16)
			format_mem(fmt->binary + fmt->offset, &current, fmt->size, mem_buf);
		ft_printf("%s", ptr_buf, mem_buf);
	}
	return (EXIT_SUCCESS);
}

/*
** determine if given segment is __text and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct section*} section to print
** @param{struct section_64*} section to print
** @return {int} 0 on success, 1 on failure
*/

int		print_text_section(t_ctx *ctx
					, struct section *section
					, struct section_64 *section_64)
{
	t_sect	section_fmt;

	if (section && !ft_strcmp("__text", section->sectname))
	{
		section_fmt.binary = ctx->file;
		section_fmt.addr = section->addr;
		section_fmt.size = section->size;
		section_fmt.offset = section->offset;
		section_fmt.is_64 = FALSE;
	}
	else if (section_64 && !ft_strcmp("__text", section_64->sectname))
	{
		section_fmt.binary = ctx->file;
		section_fmt.addr = section_64->addr;
		section_fmt.size = section_64->size;
		section_fmt.offset = section_64->offset;
		section_fmt.is_64 = TRUE;
	}
	return (print_text_contents(&section_fmt));
}

/*
** determine if given segment is __TEXT and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct segment_command*} segment to print
** @param{struct segment_command_64*} segment to print
** @return {int} 0 on success, 1 on failure
*/

int		print_text_segment(t_ctx *ctx
					, struct segment_command *segment
					, struct segment_command_64 *segment_64)
{
	if ((segment && !ft_strcmp("__TEXT", segment->segname))
		|| (segment_64 && !ft_strcmp("__TEXT", segment_64->segname)))
	{
		ft_printf("%s:\n", ctx->filename);
		ft_printf("Contents of (__TEXT,__text) section\n");
	}
	return (EXIT_SUCCESS);
}
