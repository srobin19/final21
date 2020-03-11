/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:22:17 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/13 15:14:24 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	sjoin = (char*)malloc(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1);
	if (!sjoin)
		return (NULL);
	while (s1[i])
	{
		sjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sjoin[i + j] = s2[j];
		j++;
	}
	sjoin[i + j] = '\0';
	return (sjoin);
}
