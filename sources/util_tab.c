/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:16:05 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/06 18:24:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	**init_tab(void)
{
	char	**tabs;

	if (!(tabs = malloc(sizeof(tabs) * 2)))
		exit(EXIT_FAILURE);
	if (!(tabs[0] = ft_strdup("")))
		exit(EXIT_FAILURE);
	tabs[1] = NULL;
	return (tabs);
}

size_t	get_tab_size(char **tabs)
{
	size_t	size;
	char	**roam;

	if (!tabs)
		return (0);
	roam = tabs;
	size = 0;
	while (*roam)
	{
		size++;
		roam++;
	}
	return (size);
}

void	print_tab(char **tabs)
{
	char	**curr;

	if (!tabs)
		return ;
	curr = tabs;
	while (*curr)
	{
		printf("[ %s ]\n", *curr);
		curr++;
	}
}
