/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_archive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:55:26 by tmatthew          #+#    #+#             */
/*   Updated: 2020/01/23 10:48:01 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int		validate_extended_archive(char *file, t_ctx __attribute__((unused)) *ctx)
{
	struct ar_hdr	file_header __attribute__((unused));

	file_header = *(struct ar_hdr*)(file + SARMAG);
	return (validate_file(file + SARMAG + sizeof(struct ar_hdr), ctx, TRUE));
}
