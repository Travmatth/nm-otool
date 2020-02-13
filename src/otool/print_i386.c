/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i386.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/12 16:37:40 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** determine if given segment is __text and print if it is.
** print __TEXT header, __text section contents in 16 byte rows prefixed
** with pointer address
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct section*} section to print
** @param{struct section_64*} section to print
** @return {int} 0 on success, 1 on failure
*/

int				print_i386_text_section(struct section *section
										, char *data
										, int flags __attribute__((unused)))
{
	struct section	sect;
	uint64_t		current;
	char			ptr_buf[17];
	char			mem[33];

	if (section && ft_strcmp(SECT_TEXT, section->sectname))
		return (EXIT_SUCCESS);
	ft_putendl("Contents of (__TEXT,__text) section");
	current = 0;
	while (current < sect.size)
	{
		if (!(current % 16))
		{
			format_pointer(sect.addr + current, ptr_buf, FALSE);
			ft_putstr(ptr_buf);
			ft_putstr("	");
		}
		format_mem(data, &current, sect.size, mem);
		if (!OK(print_memory_buf(flags, mem)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			print_i386_text_section(t_x86_64_text *i386)
{
	int		i;

	i = 0;
	while (i386->sections[i])
	{
		if (print_x86_64_text_section(i386->sections[i]
									, i386->data[i]
									, i386->flags[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
