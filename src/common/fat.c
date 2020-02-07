/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:17 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/06 22:34:31 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

/*
** extract FAT head from FAT binary, swap endianness if needed
** @param{file*} binary file being parsed
** @param{flags*} opts used to determine endianness
** @return {struct fat_header} fat_header on success, NULL on failure
*/

struct fat_header	*extract_fat_header(char *file, int flags)
{
	struct fat_header	*fat;

	fat = (struct fat_header*)malloc(sizeof(struct fat_header));
	if (fat == NULL)
		return (NULL);
	ft_memcpy(fat, file, sizeof(struct fat_header));
	if ((flags & SWAP))
		fat->nfat_arch = OSSwapInt32(fat->nfat_arch);
	return (fat);
}
/*
** iterate over FAT binary and parse each archived binary
** @param{t_ctx*} program context containing binary file being parsed
** @param{t_seg_f} function called with current segment being iterated over
** @param{t_sec_f} function called with current section being iterated over
** @return {int} 0 on success, 1 on failure
*/

int		dump_fat_bin(char *file, t_ctx *ctx, t_dump_fxs *dump)
{
	uint32_t			offset;
	uint32_t			nfat_arch;
	struct fat_arch		*arch;
	cpu_subtype_t		subtype;

	offset = sizeof(struct fat_header);
	nfat_arch = OSSwapInt32(((struct fat_header*)file)->nfat_arch);
	while (nfat_arch--)
	{
		arch = (struct fat_arch*)(file + offset);
		subtype = OSSwapInt32(arch->cpusubtype & CPU_SUBTYPE_MASK);
		if (OSSwapInt32(arch->cputype) == CPU_TYPE_X86_64 &&
			subtype == CPU_SUBTYPE_X86_64_ALL)
			validate_multiplex(file + OSSwapInt32(arch->offset), ctx, dump);
		else if (ctx->has_x86_64 == FALSE && OSSwapInt32(arch->cputype) == CPU_TYPE_POWERPC &&
			subtype == CPU_SUBTYPE_POWERPC_ALL)
			validate_multiplex(file + OSSwapInt32(arch->offset), ctx, dump);
		else if (ctx->has_x86_64 == FALSE && OSSwapInt32(arch->cputype) == CPU_TYPE_I386 &&
			subtype == CPU_SUBTYPE_I386_ALL)
			validate_multiplex(file + OSSwapInt32(arch->offset), ctx, dump);
		offset += sizeof(struct fat_arch);
	}
	return (EXIT_SUCCESS);
}
