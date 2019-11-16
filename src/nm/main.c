/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2019/11/15 16:22:21 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

/*
** Nm displays the name list (symbol table of nlist structures) of each object
** file in the argument list. In some cases, as with an object that has had
** strip(1) with its -T option used on the object, that can be different than
** the dyld information. For that information use dyldinfo(1).
**
** If an argument is an archive, a listing for each object file in the archive
** will be produced. File can be of the form libx.a(x.o), in which case only
** symbols from that member of the object file are listed. (The parentheses have
** to be quoted to get by the shell.) If no file is given, the symbols in
** a.out are listed.
**
** Each symbol name is preceded by its value (blanks if undefined). This value
** is followed by one of the following characters, representing the symbol type:
** U (undefined)
** A (absolute)
** T (text section symbol)
** D (data section symbol)
** B (bss section symbol)
** C (common symbol)
** - (for debugger symbol table entries; see -a below)
** S (symbol in a section other than those above)
** I (indirect symbol).
** If the symbol is local (non-external), the symbol's type is instead
** represented by the corresponding lowercase letter. A lower case u in a
** dynamic shared library indicates a undefined reference to a private external
**in another module in the same library.
**
** If the symbol is a Objective C method, the symbol name is
** +-[Class_name(category_name) method:name:], where `+' is for class methods,
** `-' is for instance methods, and (category_name) is present only when the
** method is in a category.
**
** The output is sorted alphabetically by default.
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
	nm_skeleton();
	return (EXIT_SUCCESS);
}
