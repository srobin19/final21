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

//Used for the execution of a binary file. Will split the command into
//an executable file and arguments. Redirection should be done here???
static void	execute_binary(t_tokens *pnode, char **env)
{
	char	**full_cmd;

	ft_strcmp(env[0], env[0]);//wtf?
	full_cmd = gather_cmds_tokens(pnode);
	execvp(full_cmd[0], full_cmd);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}

//This function test to see if a command is a builtin or not. If it is,
//the approriate function is called and the command executed.
static int	is_builtin(t_tokens *pnode, char ***env, t_pwd *pwd)
{
	char	**full_cmd;
	char	isbuiltin;

	isbuiltin = 0;
	full_cmd = gather_cmds_tokens(pnode);
	if (!ft_strcmp(full_cmd[0], "exit"))
		isbuiltin = 1;
	else if (!ft_strcmp(full_cmd[0], "echo"))
	{
		isbuiltin = 2;
		echo (full_cmd);
	}
	else if (!ft_strcmp(full_cmd[0], "cd"))
	{
		isbuiltin = 3;
		cd(full_cmd, env, pwd);
	}
	else if (!ft_strcmp(full_cmd[0], "env"))
	{
		isbuiltin = 4;
		printenv(*env);
	}
	else if (!ft_strcmp(full_cmd[0], "setenv"))
	{
		isbuiltin = 5;
		set_env(full_cmd, env);
	}
	else if (!ft_strcmp(full_cmd[0], "unsetenv"))
	{
		isbuiltin = 6;
		unset_env(full_cmd, env);
	}
	else if (!ft_strcmp(full_cmd[0], "type"))
		isbuiltin = 7;
	return (isbuiltin);
}

//Here the command is tested (is it a builtin or not) and executed accordingly.
//The testing (and execution) of builtin is done two times, wich is a major bug
//and design error.
static void	execute_cmd(t_tokens *pnode, char ***env, t_pwd *pwd)
{
	if (is_builtin(pnode, env, pwd))
		;
	else
		execute_binary(pnode, *env);
}

//This function will do the appropriate forks, and send the command to execution
//via execute_cmd. It seems there's a major problem here, since the fork is done
//no matter what, before testing if it's a builtin command or not.
static void	pipe_and_execute(int p[2], t_tokens *curr, char **env, t_pwd *pwd)
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
		execute_cmd(curr, env, pwd);
	}
	else if (pid > 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		wait(&pid);
	}
}

//test if the pipe node is a builtin command or not. If it is a builtin, it will do the
//redirections, keep track of them, and reset them, since a builtin is NOT forked.
//then it is either sent into the pipeline execution function, or just execute_cmd
//if this is the last node of the pipeline (or the only one obviously)
//Error: we're using is_builtin to test, but this function also execute the builtins.
//However the actual execution is (and should be?) done later, at the same stage as if
//it was an executable file being called for execution.
static int	test_and_execute(t_tokens **pnode, char ***env, t_pwd *pwd, int p[2])
{
	t_dupsave *track;

	track = NULL;
	if (is_builtin(*pnode, env, pwd))
	{
		track = redirect(*pnode);
		reset_redirections(track);	
	}
	if (*(pnode + 1))
		pipe_and_execute(p, *pnode, *env);
	else
		execute_cmd(pnode, env, pwd);
	return (1);
}

//this function loop through each elements of the pipeline, creates a pipe for each one 
//of them, and send it to a test function.
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

//WARNING: this file still contain a lot of design errors, but is gonna be described 
//as it is. This will help spot these design errors and correct them.
//
//a first fork is done, in which the pipeline is executed (this might be an error...)
//into the newly created child, we process the pipeline.
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
