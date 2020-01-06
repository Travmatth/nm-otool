/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/05 17:43:17 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** print __TEXT header, __text section contents in 16 byte rows prefixed
** with pointer address
** @param{t_addr} info on section to print
** @return {int} 0 on success, 1 on failure
*/

int		print_text_contents(t_addr *fmt)
{
	uint64_t	current;
	char		ptr_buf[17];
	char		mem_buf[49];

	ft_printf("Contents of (__TEXT,__text) section\n");
	current = 0;
	while (current < fmt->size)
	{
		if (!(current % 16))
		{
			format_pointer(fmt->addr + current, ptr_buf, fmt->is_64);
			ft_putstr(ptr_buf);
			ft_putstr("	");
		}
		format_mem(fmt->binary + fmt->offset, &current, fmt->size, mem_buf);
		ft_putendl(mem_buf);
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

int		print_i386_text_section(char *file
							, struct section *section
							, struct section_64 *section_64)
{
	t_addr	section_fmt;

	if (section && !ft_strcmp(SECT_TEXT, section->sectname))
	{
		section_fmt.binary = file;
		section_fmt.addr = (uint64_t)section->addr;
		section_fmt.size = (uint64_t)section->size;
		section_fmt.offset = (uint64_t)section->offset;
		section_fmt.is_64 = FALSE;
	}
	else if (section_64 && !ft_strcmp(SECT_TEXT, section_64->sectname))
	{
		section_fmt.binary = file;
		section_fmt.addr = section_64->addr;
		section_fmt.size = section_64->size;
		section_fmt.offset = section_64->offset;
		section_fmt.is_64 = TRUE;
	}
	else
		return (EXIT_SUCCESS);
	return (print_text_contents(&section_fmt));
}

/*
** determine if given segment is __text and print if it is.
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct section*} section to print
** @param{struct section_64*} section to print
** @return {int} 0 on success, 1 on failure
*/

int		print_x86_64_text_section(char *file
							, struct section *section
							, struct section_64 *section_64)
{
	t_addr	section_fmt;

	if (section && !ft_strcmp(SECT_TEXT, section->sectname))
	{
		section_fmt.binary = file;
		section_fmt.addr = (uint64_t)section->addr;
		section_fmt.size = (uint64_t)section->size;
		section_fmt.offset = (uint64_t)section->offset;
		section_fmt.is_64 = FALSE;
	}
	else if (section_64 && !ft_strcmp(SECT_TEXT, section_64->sectname))
	{
		section_fmt.binary = file;
		section_fmt.addr = section_64->addr;
		section_fmt.size = section_64->size;
		section_fmt.offset = section_64->offset;
		section_fmt.is_64 = TRUE;
	}
	else
		return (EXIT_SUCCESS);
	return (print_text_contents(&section_fmt));
}
