/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:38:16 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:01:59 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	dispatch(t_tokens *cmd_group)
{
	t_tokens	**toks_pseq;

	toks_pseq = split_tokens(cmd_group, PIPE);
	execute_pseq(toks_pseq);
	return (1);
}

static int	prompt_loop(void)
{
	char		*cmds;
	t_tokens	*toks_all;
	t_tokens	**toks_grp;
	t_tokens	**curr_grp;
	t_termcaps	termcaps;

	if (tcgetattr(0, &termcaps.term_restore) == -1)
		exit(-1);
	init_termcaps(&termcaps);
  	if (!(g_shell = malloc(sizeof(*g_shell))))
		exit(-1);
	cmds = NULL;
  	g_shell->termcaps = &termcaps;

	while (1)
	{
//		prompt();
		cmds = trim_termcaps(core_termcaps(&termcaps, 1));
		toks_all = lexer(cmds);
		display_ll(toks_all);
		toks_grp = split_tokens(toks_all, SMCL);
		curr_grp = toks_grp;
		while (*curr_grp)
		{
			dispatch(*curr_grp);
			curr_grp++;
		}
		ft_strdel(&cmds);
	}
	return (1);
}

int			main(void)
{
	title();
	prompt_loop();
	return (0);
}
