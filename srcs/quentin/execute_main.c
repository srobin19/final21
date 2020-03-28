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
	redirect(pnode);
	full_cmd = gather_cmds_tokens(pnode);
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

static int	builtin(t_tokens *pnode, char ***env, t_pwd *pwd)
{
	char	**full_cmd;

	full_cmd = gather_cmds_tokens(pnode);
	if (!ft_strcmp(full_cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(full_cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(full_cmd[0], "cd"))
	{
		cd(full_cmd, env, pwd);
		return (1);
	}
	else if (!ft_strcmp(full_cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(full_cmd[0], "setenv"))
	{
		set_env(full_cmd, env);
		return (1);
	}
	else if (!ft_strcmp(full_cmd[0], "unsetenv"))
		return (1);
	else if (!ft_strcmp(full_cmd[0], "type"))
		return (1);
	else
		return(0);
}

static void	process_pipeline(t_tokens **pseq, char ***env, t_pwd *pwd)
{
	int		p[2];
	t_tokens	**curr;

	curr = pseq;
	while (*(curr + 1))
	{
		if (pipe(p) < 0)
			err_handler("pipe error: ");
		if (builtin(*curr, env, pwd))
			printf("BUILTIN DETECTED\n");
		else
			pipe_and_execute(p, *curr, *env);
		curr++;
	}
	if (builtin(*curr, env, pwd))
		printf("BUILTIN DETECTED\n");
	else
		execute_binary(*curr, *env);
}

void		execute_pseq(t_tokens **pseq, t_pwd *pwd, char ***env)
{
	pid_t	pid;

	if (!pseq || !pseq[0])
		return ;
	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)
		process_pipeline(pseq, env, pwd);
	else if (pid > 0)
		wait(&pid);
}
