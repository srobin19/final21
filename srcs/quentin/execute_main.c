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

#include "21sh.h"
#include "q21sh.h"

static int	err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void	execute_binary(t_tokens *pnode, char **env)
{
	char	**full_cmd;

	ft_strcmp(env[0], env[0]);
	full_cmd = gather_cmds_tokens(pnode);
	redirect(pnode);
	execvp(full_cmd[0], full_cmd);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

static void	pipe_and_execute(int p[2], t_tokens *curr, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		execute_binary(curr, env);
	}
	else if (pid > 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		wait(&pid);
	}
}

static int	is_builtin(t_tokens *pnode, char ***env, t_pwd *pwd)
{
	char	**full_cmd;
	char	isbuiltin;

	isbuiltin = 0;
	full_cmd = gather_cmds_tokens(pnode);
	if (!ft_strcmp(full_cmd[0], "exit"))
		isbuiltin = 1;
	else if (!ft_strcmp(full_cmd[0], "echo"))
		isbuiltin = 2;
	else if (!ft_strcmp(full_cmd[0], "cd"))
	{
		printf("doing cd..\n");
		isbuiltin = 3;
		cd(full_cmd, env, pwd);
	}
	else if (!ft_strcmp(full_cmd[0], "env"))
		isbuiltin = 4;
	else if (!ft_strcmp(full_cmd[0], "setenv"))
	{
		isbuiltin = 5;
		set_env(full_cmd, env);
	}
	else if (!ft_strcmp(full_cmd[0], "unsetenv"))
		isbuiltin = 6;
	else if (!ft_strcmp(full_cmd[0], "type"))
		isbuiltin = 7;
	return (isbuiltin);
}

static int	test_and_execute(t_tokens **pnode, char ***env, t_pwd *pwd, int p[2])
{
	t_dupsave *track;

	track = NULL;
	if (is_builtin(*pnode, env, pwd))
	{
		track = redirect(*pnode);
		reset_redirections(track);	
	}
	else if (*(pnode + 1))
		pipe_and_execute(p, *pnode, *env);
	else
		execute_binary(*pnode, *env);
	return (1);
}

static int	process_pipeline(t_tokens **pseq, char ***env, t_pwd *pwd)
{
	int		p[2];
	t_tokens	**curr;

	curr = pseq;
	while (*curr)
	{
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		test_and_execute(curr, env, pwd, p);
		curr++;
	}
	return (1);
}

int		execute_pseq(t_tokens **pseq, t_pwd *pwd, char ***env)
{
	pid_t	pid;

	if (!pseq || !pseq[0])
		return (0);
	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)
		process_pipeline(pseq, env, pwd);
	else if (pid > 0)
		wait(&pid);
	return (1);
}
