/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:41:31 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/06 18:14:33 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	get_size(char **array)
{
	size_t	size;
	char	**ptr;

	ptr = array;
	size = 0;
	while (*ptr)
	{
		size++;
		ptr++;
	}
	return (size + 2);
}

char			**fresh_array(char *new_entry)
{
	char	**new_array;

	if (!(new_array = malloc(sizeof(new_array) * 2)))
		exit(EXIT_FAILURE);
	if (!(new_array[0] = ft_strdup(new_entry)))
		exit(EXIT_FAILURE);
	new_array[1] = NULL;
	return (new_array);
}
char			**ft_realloc_array(char **old_array, char *new_entry)
{
	char	**new_array;
	char	**roam_o;
	char	**roam_n;

	if (!new_entry)
		return (NULL);
	if (!old_array)
		return (fresh_array(new_entry));
	if (!(new_array = malloc(sizeof(new_array) * get_size(old_array))))
		exit(EXIT_FAILURE);
	roam_n = new_array;
	roam_o = old_array;
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
	ft_free_array2(old_array);
	return (new_array);
}
