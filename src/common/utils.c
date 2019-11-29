/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:00 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/28 21:59:50 by tmatthew         ###   ########.fr       */
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
** determine if given file is FAT, 32/64bit Mach-O binary, or archive
** @param {t_ctx*} struct containing file
** @return {int} 0 on success, 1 on error
*/

int			determine_file(t_ctx *ctx)
{
	uint32_t	magic;

	magic = *(uint32_t*)ctx->file;
	if (is_fat32(ctx, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_fat64(ctx, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_mach32(ctx, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (is_mach64(ctx, magic) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (is_archive(ctx));
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
