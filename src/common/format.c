/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:20:18 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/04 00:05:28 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** generate string representation of given pointer as '0' prefixed string
** @param{uint64_t} address to format as string
** @param{char[]} buffer to store string
** @param{int} size of outputted string
*/

void	format_pointer(uint64_t addr, char ptr_buf[], int is_64)
{
	int		len;

	len = is_64 ? 15 : 7;
	ptr_buf[len + 1] = '\0';
	while (len >= 0)
	{
		ptr_buf[len--] = HEX_CHARS[(addr & 0xff) % 16];
		addr /= 16;
	}
}

/*
** generate string representation of given memory buffer
** @param{char*} memory region to extract into buffer
** @param{uint64_t} current offset to be transformed to string
** @param{uint64_t} total size of memory to extract
** @param{char[]} buffer to store string
*/

void	format_mem(char *binary, uint64_t *offset, uint64_t size, char mem_buf[])
{
	uint64_t		bin_i;
	int				buf_i;

	buf_i = 0;
	bin_i = *offset;
	size = (size - *offset) > 16 ? 16 : (size - *offset);
	*offset = *offset + size;
	while (size-- > 0)
	{
		mem_buf[buf_i++] = HEX_CHARS[((binary[bin_i] >> 4) & 0xf)];
		mem_buf[buf_i++] = HEX_CHARS[(binary[bin_i++] & 0xf)];
		mem_buf[buf_i++] = ' ';
	}
	mem_buf[buf_i] = '\0';
}

