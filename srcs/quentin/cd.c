/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:30:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 18:06:02 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

void		check_access(char *path)
{
	struct stat st;

	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr(path);
	if (access(path, F_OK))
		ft_putendl_fd(": no such file or directory", 2);
	else if (access(path, R_OK))
		ft_putendl_fd(": permission denied", 2);
	else if (!lstat(path, &st) && !S_ISDIR(st.st_mode))
		ft_putendl_fd(": not a directory", 2);
	else
		ft_putendl_fd(": unidentified error", 2);
}

static void	chdir_home(char ***env, t_pwd *pwd)
{
	char	*home;
	char	*tmp;

	if (!(home = get_env_var(*env, "HOME")))
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (chdir(home))
		check_access(home);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", home);
		update_s_pwd(pwd);
	}
	if (home)
		free(home);
}

static void	chdir_oldpwd(char ***env, t_pwd *pwd)
{
	char	*tmp;

	if (chdir(pwd->old_wd))
		check_access(pwd->old_wd);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", pwd->old_wd);
		update_s_pwd(pwd);
	}
}

static void	chdir_arg(char *path, char ***env, t_pwd *pwd)
{
	char	*tmp;

	if (chdir(path))
		check_access(path);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", path);
		update_s_pwd(pwd);
	}
}

void		cd(char **cmd, char ***env, t_pwd *pwd)
{
	if (ft_tablen(cmd) == 1)
		chdir_home(env, pwd);
	else if (!ft_strcmp(cmd[1], "-"))
		chdir_oldpwd(env, pwd);
	else
		chdir_arg(cmd[1], env, pwd);
}
