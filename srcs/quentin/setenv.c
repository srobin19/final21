/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:23:21 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 20:18:38 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

char	**set_env(char **cmd, char ***env)
{
	char	*tmp;

	if (!cmd[1])
	{
		printenv(*env);
		return (*env);
	}
	if (cmd[2] && cmd[3])
	{
		ft_putendl_fd("minishell: setenv: too many arguments.", 2);
		return (*env);
	}
	if (replace_env(cmd, *env) == 1)
		return (*env);
	else
	{
		if (cmd[2])
			tmp = set_var(NULL, cmd[1], cmd[2]);
		else
			tmp = set_var(NULL, cmd[1], "");
		*env = ft_realloc_array(*env, tmp);
		free(tmp);
	}
	return (*env);
}

int		replace_env(char **cmd, char **env)
{
	char	**roam;

	roam = env;
	while (*roam)
	{
		if (env_match(cmd[1], *roam))
		{
			if (cmd[2])
				*roam = set_var(*roam, cmd[1], cmd[2]);
			else
				*roam = set_var(*roam, cmd[1], "");
			return (1);
		}
		roam++;
	}
	return (0);
}

int		env_match(char *to_find, char *curr_var)
{
	size_t	len;

	len = ft_strlen(to_find);
	if (!ft_strncmp(to_find, curr_var, len) && curr_var[len] == '=')
		return (1);
	else
		return (0);
}

char	*set_var(char *to_set, char *name, char *value)
{
	char	*new_var;
	int		i;
	int		j;

	if (to_set)
		free(to_set);
	if (!(new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2)))
		exit(EXIT_FAILURE);
	i = 0;
	while (name[i])
	{
		new_var[i] = name[i];
		i++;
	}
	new_var[i] = '=';
	i++;
	j = 0;
	while (value[j])
	{
		new_var[i] = value[j];
		i++;
		j++;
	}
	new_var[i] = '\0';
	return (new_var);
}
