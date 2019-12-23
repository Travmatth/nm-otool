/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2019/12/22 16:45:01 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

/*
** The objdump(1) option to display the contents of the (__TEXT,__text)
** section is to use the -section __TEXT,__text option. If disassembly is
** wanted as with the -tv otool(1) options then the objdump(1) -disassemble
** is used. By default obj- dump(1)  also  symbolically disassembles the
** operands as the otool(1) -tV options will do.  If this is not wanted then the
** objdump(1) -no-symbolic-operands  option can be used.
**
** @param {int} argc - number of arguments passed to program
** @param {*char[]} argv - the arguments passed to program
** @param {*const envp[]} envp - the environment variables passed to program
** @return {int} 0 on success, 1 on failure
*/

int		otool_main(int argc, char *argv[], char *envp[])
{
	t_ctx			ctx;
	t_dump_fxs	func;

	func.header = NULL;
	func.segment = NULL;
	func.section = print_text_section;
	func.load = NULL;
	if (get_file(argc, argv, envp, &ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if ((ctx.flags & IS_FAT) && dump_fat_bin(ctx.file, &ctx, &func) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if ((ctx.flags & IS_32) && dump_macho_bin(ctx.file, &ctx, &func) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (dump_macho64_bin(ctx.file, &ctx, &func) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (cleanup_ctx(&ctx));
}
