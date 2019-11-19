/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/18 18:50:40 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

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

int		main(int argc, char *argv[], char *envp[])
{
	t_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_ctx));
	if (get_file(argc, argv, envp, &ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (determine_file(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if ((ctx.flags & IS_FAT) && dump_fat_segs(&ctx
		, &print_section
		, &print_section64) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (dump_mach_segs(&ctx
		, &print_section
		, &print_section64) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (cleanup_ctx(&ctx));
}
