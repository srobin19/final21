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

//This function splits a command group into a pipeline sequence,
//which is an array of lists that each contain the different
//tokens of a pipeline element, ex:
//for: cmd1 arg1 arg2 >redir | cmd2 arg1 | >redir cmd3
//- elem1: cmd1 arg1 arg2 <redir
//- elem2: cmd2 arg1
//- elem3: >redir cmd3
//of course if there's no pipes, it will only contain one list.
//then it's send into execution (execute_main.c)
static int	dispatch(t_tokens *cmd_group, t_pwd *pwd, char ***env)
{
	t_tokens	**toks_pseq;

	toks_pseq = split_tokens(cmd_group, PIPE);
	execute_pseq(toks_pseq, pwd, env);
	return (1);
}

//?
t_shell *g_shell;

void		sig(int nb)
{
    nb = 0;
    g_shell->termcaps->i = 1;
		ft_putstr("\n\n");
		choose_display(g_shell->termcaps);
	return ;
}

//- This is the main loop that prompt the user for commands and then
//  call the functions that will process these inputs:
//  - get the user input into a list of tokens (trim_termcaps.c?, tokens_main.c)
//  - split it into command groups regarding semicolumns (;)(tokens_split.c)
//  - send each groups to the dispatch function
//- It also init and link the termcaps functions to the main prompt.
int	prompt_loop(char ***env, t_pwd *pwd)
{
	char		*cmds;
	t_tokens	*toks_all;
	t_tokens	**toks_grp;
	t_tokens	**curr_grp;
	t_termcaps	termcaps;

	//setting up termcaps
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
		display_ll(toks_all);//display tokens, just for testing
		toks_grp = split_tokens(toks_all, SMCL);
		curr_grp = toks_grp;
		while (*curr_grp)
		{
			dispatch(*curr_grp, pwd, env);
			curr_grp++;
		}
	}
	return (1);
}
