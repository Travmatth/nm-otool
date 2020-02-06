/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_archive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:55:26 by tmatthew          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/01/23 10:48:01 by tmatthew         ###   ########.fr       */
=======
/*   Updated: 2020/02/05 22:49:03 by tmatthew         ###   ########.fr       */
>>>>>>> basic archive parsing
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		validate_extended_archive(char *file, t_ctx *ctx)
{
<<<<<<< HEAD
	struct ar_hdr	file_header __attribute__((unused));

	file_header = *(struct ar_hdr*)(file + SARMAG);
	return (validate_file(file + SARMAG + sizeof(struct ar_hdr), ctx, TRUE));
=======
	char			*name;
	char			*object;
	uint64_t		file_size;
	struct ar_hdr	file_header;

	file_size = SARMAG;
	while (TRUE)
	{
		if (file + file_size >= ctx->file + ctx->size)
			break ;
		file_header = *(struct ar_hdr*)(file + file_size);
		name = file + file_size + sizeof(struct ar_hdr);
		object = name + ft_atoi(&file_header.ar_name[3]);
		if (determine_file(object, ctx) == EXIT_SUCCESS
			&& validate_file(object, ctx, TRUE) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		file_size += ft_atoi(file_header.ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
>>>>>>> basic archive parsing
}
