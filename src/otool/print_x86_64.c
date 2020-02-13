/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x86_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/12 17:25:32 by tmatthew         ###   ########.fr       */
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

int				print_x86_64_text_section(struct section_64 *section
										, char *data
										, int flags __attribute__((unused)))
{
	uint64_t	current;
	char		ptr_buf[17];
	char		mem[33];

	ft_putendl("Contents of (__TEXT,__text) section");
	current = 0;
	while (current < section->size)
	{
		if (!(current % 16))
		{
			format_pointer(section->addr + current, ptr_buf, TRUE);
			ft_putstr(ptr_buf);
			ft_putstr("	");
		}
		format_mem(data, &current, section->size, mem);
		if (!OK(print_memory_buf(FALSE, mem)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			print_x86_64_text_sections(t_x86_64_text *x86_64)
{
	int		i;

	i = 0;
	while (x86_64->sections[i])
	{
		if (print_x86_64_text_section(x86_64->sections[i]
									, x86_64->data[i]
									, x86_64->flags[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
