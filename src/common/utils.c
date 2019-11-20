/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:19:00 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/19 16:40:56 by tmatthew         ###   ########.fr       */
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
		ctx->size = f_stat.st_size;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** determine if given file is FAT or 32/64bit Mach-O binary
** @param {t_ctx*} struct containing file
** @return {int} 0 on success, 1 on error
*/

int			determine_file(t_ctx *ctx)
{
	uint32_t	magic;

	magic = *(uint32_t*)ctx->file;
	if (magic == MH_MAGIC)
		ctx->flags |= IS_32;
	else if (magic == MH_CIGAM)
	{
		ctx->flags |= IS_32;
		ctx->flags |= IS_SWAPPED;
	}
	else if (magic == MH_CIGAM_64)
		ctx->flags |= IS_SWAPPED;
	else if (magic == FAT_MAGIC)
		ctx->flags |= IS_FAT;
	else if (magic == FAT_CIGAM)
	{
		ctx->flags |= IS_FAT;
		ctx->flags |= IS_SWAPPED;
	}
	else if (magic != MH_MAGIC_64)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** swap the bytes of 32bit integer to different endianness
** @param {uint32_t} old integer to swap
** @return {uint32_t} swapped integer
*/

uint32_t	swap_uint32(uint32_t old)
{
	uint32_t	new;

	new = ((old & 0xff000000) >> 24) |
		((old & 0x00ff0000) >> 8) |
		((old & 0x0000ff00) << 8) |
		((old & 0x000000ff) << 24);
	return (new);
}

/*
** swap the bytes of 64bit integer to different endianness
** @param {uint64_t} old integer to swap
** @return {uint64_t} swapped integer
*/

uint64_t	swap_uint64(uint64_t old)
{
	uint64_t	new;

	new = ((old & 0xff00000000000000ULL) >> 56) | \
		((old & 0x00ff000000000000ULL) >> 40) | \
		((old & 0x0000ff0000000000ULL) >> 24) | \
		((old & 0x000000ff00000000ULL) >> 8) | \
		((old & 0x00000000ff000000ULL) << 8) | \
		((old & 0x0000000000ff0000ULL) << 24) | \
		((old & 0x000000000000ff00ULL) << 40) | \
		((old & 0x00000000000000ffULL) << 56);
	return (new);
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
