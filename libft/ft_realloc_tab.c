/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:41:31 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/06 18:14:33 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	get_size(char **tab)
{
	size_t	size;
	char	**ptr;

	ptr = tab;
	size = 0;
	while (*ptr)
	{
		size++;
		ptr++;
	}
	return (size + 2);
}

char			**fresh_tab(char *new_entry)
{
	char	**new_tab;

	if (!(new_tab = malloc(sizeof(new_tab) * 2)))
		exit(EXIT_FAILURE);
	if (!(new_tab[0] = ft_strdup(new_entry)))
		exit(EXIT_FAILURE);
	new_tab[1] = NULL;
	return (new_tab);
}
char			**ft_realloc_tab(char **old_tab, char *new_entry)
{
	char	**new_tab;
	char	**roam_o;
	char	**roam_n;

	if (!new_entry)
		return (NULL);
	if (!old_tab)
		return (fresh_tab(new_entry));
	if (!(new_tab = malloc(sizeof(new_tab) * get_size(old_tab))))
		exit(EXIT_FAILURE);
	roam_n = new_tab;
	roam_o = old_tab;
	while (*roam_o)
	{
		if (!(*roam_n = ft_strdup(*roam_o)))
			exit(EXIT_FAILURE);
		roam_o++;
		roam_n++;
	}
	if (!(*roam_n = ft_strdup(new_entry)))
		exit(EXIT_FAILURE);
	roam_n++;
	*roam_n = NULL;
	ft_free_tab2(old_tab);
	return (new_tab);
}
