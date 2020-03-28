/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:16:05 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/06 18:24:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

char	**init_array(void)
{
	char	**array;

	if (!(array = malloc(sizeof(array) * 2)))
		exit(EXIT_FAILURE);
	if (!(array[0] = ft_strdup("")))
		exit(EXIT_FAILURE);
	array[1] = NULL;
	return (array);
}

size_t	get_array_size(char **array)
{
	size_t	size;
	char	**roam;

	if (!array)
		return (0);
	roam = array;
	size = 0;
	while (*roam)
	{
		size++;
		roam++;
	}
	return (size);
}

void	print_array(char **array)
{
	char	**curr;

	if (!array)
		return ;
	curr = array;
	while (*curr)
	{
		printf("[ %s ]\n", *curr);
		curr++;
	}
}
