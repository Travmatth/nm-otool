/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:51:03 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/28 23:11:17 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "common.h"

/*
** struct containing information needed to print section
** char *binary: file to be parsed
** uint32_t addr: address of section once loaded in memory
** uint32_t size: size of section
** uint32_t offset: offset of section in binary
** int is_64: whether file is a 64-bit binary
*/

typedef struct	s_sect
{
	char		*binary;
	uint32_t	addr;
	uint32_t	size;
	uint32_t	offset;
	int			is_64;
}				t_sect;

int		print_text_section(t_ctx *ctx
						, struct section *section
						, struct section_64 *section_64);
int		print_text_segment(t_ctx *ctx
						, struct segment_command *segment_command
						, struct segment_command_64 *segment_command_64);
#endif
