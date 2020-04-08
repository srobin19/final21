/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:10:32 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 20:21:12 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

void	update_s_pwd(t_pwd *pwd)
{
	char	tmp[PATH_MAX + 1];

	free(pwd->old_wd);
	pwd->old_wd = ft_strdup(pwd->current_wd);
	free(pwd->current_wd);
	if (!(getcwd(tmp, PATH_MAX + 1)))
		exit(EXIT_FAILURE);
	pwd->current_wd = ft_strdup(tmp);
}

int		update_pwd(char ***env, char *var, char *value)
{
	char	**roam;

	roam = *env;
	while (*roam)
	{
		if (env_match(var, *roam))
		{
			*roam = set_var(*roam, var, value);
			return (1);
		}
		roam++;
	}
	return (0);
}

int		init_pwd(t_pwd *pwd)
{
	char tmp[PATH_MAX + 1];

	if (!(getcwd(tmp, PATH_MAX + 1)))
		return (0);
	if (!(pwd->current_wd = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	if (!(pwd->old_wd = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	return (1);
}

void	free_pwd(t_pwd *pwd)
{
	free(pwd->current_wd);
	free(pwd->old_wd);
}
