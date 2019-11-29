/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:20:18 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/28 23:37:45 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** generate string representation of given pointer as '0' prefixed string
** @param{uint32_t} address to format as string
** @param{char[]} buffer to store string
** @param{int} size of outputted string
*/

void	format_pointer(uint32_t offset, char ptr_buf[], int is_64)
{
	(void)offset;
	(void)ptr_buf;
	(void)is_64;
}

/*
** generate string representation of given memory buffer
** @param{char*} __text section to extract into buffer
** @param{uint32_t} current offset that has been transformed to string
** @param{uint32_t} total size of memory to extract
** @param{char[]} buffer to store string
*/

void	format_mem(char *binary, uint32_t *current, uint32_t size, char mem_buf[])
{
	(void)binary;
	(void)current;
	(void)size;
	(void)mem_buf;
}

