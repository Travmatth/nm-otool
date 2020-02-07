/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/06 16:55:23 by tmatthew         ###   ########.fr       */
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
	t_ctx		ctx;
	t_dump_fxs	func;
	int			status;

	func.header = NULL;
	func.segment = NULL;
	func.x86_64_section = print_x86_64_text_section;
	func.i386_section = print_i386_text_section;
	func.load = NULL;
	ft_bzero(&ctx, sizeof(t_ctx));
	if (get_file(argc, argv, envp, &ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = validate_multiplex(ctx.file, &ctx, &func);
	if (cleanup_ctx(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (status);
}
