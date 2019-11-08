/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/07 18:02:21 by tmatthew         ###   ########.fr       */
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
*/

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	common_test();
	otool_skeleton();
	return (EXIT_SUCCESS);
}
