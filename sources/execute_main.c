/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:07:50 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:08:27 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void	execute(t_tokens *pnode)
{
	char	**full_cmd;

	redirect(pnode);
	full_cmd = gather_cmds_tokens(pnode);
	execvp(full_cmd[0], full_cmd);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

static void	execute_pipeline(t_tokens **pseq)
{
	int		p[2];
	pid_t		pid;
	t_tokens	**curr;

	curr = pseq;
	while (*(curr + 1))
	{
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		pid = fork();
		if (pid < 0)
			err_handler("fork error: ");
		else if (pid == 0)
		{
			close(p[0]);
			dup2(p[1], 1);
			close(p[1]);
			execute(*curr);
		}
		else if (pid > 0)
		{
			close(p[1]);
			dup2(p[0], 0);
			close(p[0]);
			wait(&pid);
		}
		curr++;
	}
	execute(*curr);
}

void		execute_pseq(t_tokens **pseq)
{
	pid_t	pid;

	if (!pseq || !pseq[0])
		return ;
	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)
			execute_pipeline(pseq);
	else if (pid > 0)
		wait(&pid);
}
