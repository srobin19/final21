/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:32:36 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:05:51 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*get_env_var(char **env, char *var_name)
{
	char	*var_content;
	char	**roam;
	size_t	var_len;

	if (!env || !*env || !var_name)
		return (NULL);
	var_len = 0;
	var_len = ft_strlen(var_name);
	roam = env;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var_name, var_len))
		{
			if (!(var_content = ft_strdup(*roam + var_len + 1)))
				exit(EXIT_FAILURE);
			return (var_content);
		}
		roam++;
	}
	return (NULL);
}

char	**get_env(char **environ)
{
	char	**copy;
	char	**env_ptr;
	char	**cpy_ptr;

	if (!environ)
		return (NULL);
	if (!(copy = malloc(sizeof(copy) * (get_tab_size(environ) + 1))))
		exit(EXIT_FAILURE);
	env_ptr = environ;
	cpy_ptr = copy;
	while (*env_ptr)
	{
		if (!(*cpy_ptr = ft_strdup(*env_ptr)))
			exit(EXIT_FAILURE);
		cpy_ptr++;
		env_ptr++;
	}
	*cpy_ptr = NULL;
	return (copy);
}
