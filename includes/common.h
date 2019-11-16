/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:39 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/15 18:04:41 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMMON_H
# define FT_COMMON_H

# ifndef LIBFT_H
#  include "../libftprintf/srcs/includes/ft_printf.h"
# endif

/*
** fcntl.h - open
** sys/stat.h - fstat
** sys/mman.h - mmap/PROT_READ/PROT_WRITE/MAP_PRIVATE/MAP_FAILED
*/

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define MMAP_PROT (PROT_READ | PROT_WRITE)
# define MMAP_FLAGS (MAP_PRIVATE)

int			get_file(int argc, char **argv, char **envp, char **file);
uint32_t	swap_uint32(uint32_t old);
uint64_t	swap_uint64(uint64_t old);

/*
** Debug statements used when compiled with __DEBUG__ variable defined
*/

# ifdef __DEBUG__
#  define DEBUG_LOG(fmt, ...) ft_dprintf(STDERR_FILENO, fmt, __VA_ARGS__)
#  define DEBUG_PRINT(str) ft_dprintf(STDERR_FILENO, str)
# else
#  define DEBUG_LOG(fmt, ...) PASS
#  define DEBUG_PRINT(str) PASS
# endif
#endif
