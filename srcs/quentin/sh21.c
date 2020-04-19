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

#include "21sh.h"
#include "q21sh.h"

static int	dispatch(t_tokens *cmd_group, t_pwd *pwd, char ***env)
{
	t_tokens	**toks_pseq;

	toks_pseq = split_tokens(cmd_group, PIPE);
	execute_pseq(toks_pseq, pwd, env);
	return (1);
}

t_shell *g_shell;

void		sig(int nb)
{
    nb = 0;
    g_shell->termcaps->i = 1;
		ft_putstr("\n\n");
		choose_display(g_shell->termcaps);
	return ;
}

int	prompt_loop(char ***env, t_pwd *pwd)
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
		prompt();
		g_shell->termcaps->i = 0;
    		signal(SIGINT, sig);
		ft_putstr("\n");
		if (!(cmds = trim_termcaps(core_termcaps(&termcaps, 1))))
			continue ;
		toks_all = lexer(cmds, *env);
		display_ll(toks_all);
		toks_grp = split_tokens(toks_all, SMCL);
		curr_grp = toks_grp;
		while (*curr_grp)
		{
			dispatch(*curr_grp, pwd, env);
			curr_grp++;
		}
	}
	printf("prompt_loop end\n");
	return (1);
}
