/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:00 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/12 17:33:50 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

uint32_t		uint32_pow(uint32_t base, uint32_t power)
{
	uint32_t	half;

	if (power >= MAX_SECTION_ALIGNMENT)
		return (UINT32_MAX);
	else if (power == 0)
		return (1);
	else if (power == 1)
		return (base);
	half = uint32_pow(base, power / 2);
	return (half * half * (power % 2 ? base : 1));
}

/*
** opens file passed in argv[1], verifies not a dir, maps it to **file
** @param {int} # of args passed to program
** @param {char**} args passed to program
** @param {char**} env vars of calling process
** @param {char**} file pointer to store mapped binary
** @return {int} 0 on success, 1 on error
*/

int			get_file(int argc, char **argv, char **envp, t_ctx *ctx)
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
	else if ((ctx->file = mmap(NULL, f_stat.st_size, MMAP_PROT
				, MMAP_FLAGS, fd, 0)) == MAP_FAILED)
		DEBUG_LOG("Error: failed mappping %s into memory\n", argv[1]);
	else
	{
		ctx->filename = argv[1];
		ctx->size = f_stat.st_size;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** munmap and free memory allocated to the t_ctx struct
** @param{t_ctx*} struct processed for the given binary file
*/

int			cleanup_ctx(t_ctx *ctx)
{
	if (munmap(ctx->file, ctx->size) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
