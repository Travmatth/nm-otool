/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i386.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:36:48 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/06 11:45:33 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

void	extract_section(t_ctx *ctx, struct section *section, struct section *sect)
{
	if (ctx->flags & SWAP)
	{
		sect->size = OSSwapInt32(section->size);
		sect->addr = OSSwapInt32(section->addr);
		sect->offset = OSSwapInt32(section->offset);
	}
	else
	{
		sect->size = section->size;
		sect->addr = section->addr;
		sect->offset = section->offset;
	}
}

/*
** determine if given segment is __text and print if it is.
** print __TEXT header, __text section contents in 16 byte rows prefixed
** with pointer address
** @param{t_ctx*} program context containing binary file being parsed
** @param{struct section*} section to print
** @param{struct section_64*} section to print
** @return {int} 0 on success, 1 on failure
*/

int		print_i386_text_section(char *file, t_ctx *ctx, struct section *section)
{
	struct section sect;
	uint64_t		current;
	char			ptr_buf[17];
	char			mem_buf[33];

	if (section && ft_strcmp(SECT_TEXT, section->sectname))
		return (EXIT_SUCCESS);
	ft_putendl("Contents of (__TEXT,__text) section");
	extract_section(ctx, section, &sect);
	current = 0;
	while (current < sect.size)
	{
		if (!(current % 16))
		{
			format_pointer(sect.addr + current, ptr_buf, FALSE);
			ft_putstr(ptr_buf);
			ft_putstr("	");
		}
		format_mem(file + sect.offset, &current, sect.size, mem_buf);
		if (!OK(print_memory_buf(ctx->flags & SWAP, mem_buf)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
