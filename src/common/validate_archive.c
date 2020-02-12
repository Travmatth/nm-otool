/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_archive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:55:26 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/12 07:53:36 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		validate_extended_archive(char *file, t_ctx *ctx)
{
	int				flags;
	char			*name;
	char			*object;
	uint64_t		file_size;
	struct ar_hdr	file_header;

	file_size = SARMAG;
	while (TRUE)
	{
		flags = 0;
		if (file + file_size >= ctx->file + ctx->size)
			break ;
		file_header = *(struct ar_hdr*)(file + file_size);
		name = file + file_size + sizeof(struct ar_hdr);
		object = name + ft_atoi(&file_header.ar_name[3]);
		if (determine_magic(object, &flags) == EXIT_SUCCESS
			&& validate_file(object, ctx, flags, FALSE) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		file_size += ft_atoi(file_header.ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
