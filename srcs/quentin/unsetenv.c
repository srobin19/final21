/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:07:50 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 19:58:21 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

static int	is_envv(char *var, char **env)
{
	char 	**roam;
	size_t	len;

	roam = env;
	while (*roam)
	{
		len = 0;
		while ((*roam)[0] && (*roam)[len] != '=')
			len++;
		if (!ft_strncmp(*roam, var, len) && ft_strlen(var) == len)
			return (1);
		roam++;
	}
	return (0);
}

static char	**remove_var(char *var, char **env)
{
	char **upd_tab;
	char **roam_n;
	char **roam_o;

	if (!(upd_tab = malloc(sizeof(upd_tab) * ft_tablen(env))))
		exit(EXIT_FAILURE);
	roam_n = upd_tab;
	roam_o = env;
	while (*roam_o)
	{
		if (ft_strncmp(*roam_o, var, ft_strlen(var)))
		{
			*roam_n = ft_strdup(*roam_o);
			roam_n++;
		}
		roam_o++;
	}
	*roam_n = NULL;
	ft_freetab(env);
	return (upd_tab);
}

char		**unset_env(char **cmd, char ***env)
{
	char **roam;

	if (!cmd[1])
	{
		ft_putendl_fd("21sh: unsetenv: too few arguments", 2);
		return (*env);
	}
	roam = cmd + 1;
	while (*roam)
	{
		if (is_envv(*roam, *env))
			*env = remove_var(*roam, *env);
		roam++;
	}
	return (*env);
}
