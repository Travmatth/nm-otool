/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:00 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/15 18:22:10 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** opens file passed in argv[1], verifies not a dir, maps it to **file
** @param {int} # of args passed to program
** @param {char**} args passed to program
** @param {char**} env vars of calling process
** @param {char**} file pointer to store mapped binary
** @return {int} 0 on success, 1 on error
*/

int		get_file(int argc, char **argv, char **envp, char **file)
{
	int			fd;
	struct stat	f_stat;

	(void)envp;
	if (argc < 2)
		ft_printf("usage: ./ft_otool <FILE> \n");
	else if ((fd = open(argv[1], O_RDONLY)) == ERROR)
		DEBUG_LOG("Error: could not open %s\n", argv[1]);
	else if (fstat(fd, &f_stat) == ERROR)
		DEBUG_LOG("Error: could determine file stats: %s\n", argv[1]);
	else if (f_stat.st_mode & S_IFDIR)
		DEBUG_LOG("Error: %s is a directory\n", argv[1]);
	else if ((*file = mmap(NULL, f_stat.st_size, MMAP_PROT
				, MMAP_FLAGS, fd, 0)) == MAP_FAILED)
		DEBUG_LOG("Error: failed mappping %s into memory\n", argv[1]);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

uint32_t	swap_uint32(uint32_t old)
{
	uint32_t	new;

	new = ((old & 0xff000000) >> 24) |
		((old & 0x00ff0000) >> 8) |
		((old & 0x0000ff00) << 8) |
		((old & 0x000000ff) << 24);
	return (new);
}

uint64_t	swap_uint64(uint64_t old)
{
	uint64_t	new;

	new = ((old & 0xff00000000000000ULL) >> 56) | \
		((old & 0x00ff000000000000ULL) >> 40) | \
		((old & 0x0000ff0000000000ULL) >> 24) | \
		((old & 0x000000ff00000000ULL) >>  8) | \
		((old & 0x00000000ff000000ULL) <<  8) | \
		((old & 0x0000000000ff0000ULL) << 24) | \
		((old & 0x000000000000ff00ULL) << 40) | \
		((old & 0x00000000000000ffULL) << 56);
	return (new);
}
