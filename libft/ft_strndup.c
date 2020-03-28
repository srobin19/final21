/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:54:06 by bjovanov          #+#    #+#             */
/*   Updated: 2018/10/04 11:54:07 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*copy;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(src);
	if (n > size)
		n = size;
	copy = ft_strnew(n);
	if (copy == NULL)
		return (NULL);
	while (src[i] && i < n)
	{
		copy[i] = src[i];
		i++;
	}
	return (copy);
}
