/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatthew <tmatthew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:52:13 by tmatthew          #+#    #+#             */
/*   Updated: 2020/02/14 15:43:00 by tmatthew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/otool.h"

void	load_parse_functionality(t_ctx *ctx)
{
	ctx->hook.i386_header = NULL;
	ctx->hook.x86_64_header = NULL;
	ctx->hook.i386_segment = NULL;
	ctx->hook.x86_64_segment = NULL;
	ctx->hook.i386_section = save_i386_section;
	ctx->hook.x86_64_section = save_x86_64_section;
}

int		print_objects(t_ctx *ctx)
{
	ft_putstr(ctx->filename);
	if (ctx->out.i386_text.sections[0])
	{
		ft_putstr(" ");
		if (ctx->out.i386_text.flags[0] & SWAP)
			ft_putstr("(architecture ppc)");
		else
			ft_putstr("(architecture i386)");
	}
	ft_putendl(":");
	if (ctx->out.x86_64_text.sections[0])
		return (print_x86_64_text_sections(&ctx->out.x86_64_text));
	return (print_i386_text_sections(&ctx->out.i386_text));
}

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
	int			status;

	ft_bzero(&ctx, sizeof(t_ctx));
	load_parse_functionality(&ctx);
	if (get_file(argc, argv, envp, &ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = validate_unknown(ctx.file, &ctx);
	print_objects(&ctx);
	if (cleanup_ctx(&ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (status);
}
