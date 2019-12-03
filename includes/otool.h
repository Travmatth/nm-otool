/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:51:03 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/02 11:31:12 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "common.h"

/*
** struct containing information needed to print a section
** uint64_t addr: address of pointer to be printed
** uint64_t size: size of section
** uint64_t offset: offset of section in binary
** int is_64: whether file is a 64-bit binary
*/

typedef struct	s_sect
{
	char		*binary;
	uint64_t	addr;
	uint64_t	size;
	uint64_t	offset;
	int			is_64;
}				t_addr;

int		print_text_section(t_ctx *ctx
						, struct section *section
						, struct section_64 *section_64);
int		print_text_segment(t_ctx *ctx
						, struct segment_command *segment_command
						, struct segment_command_64 *segment_command_64);
#endif
