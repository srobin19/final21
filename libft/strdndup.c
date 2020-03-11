/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:48:47 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/10 19:50:17 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t len)
{
	char	*buffer;
	size_t	length;

	buffer = (char*)malloc((sizeof(char) * len) + 1);
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s1, len);
	*(buffer + len) = '\0';
	return (buffer);
}
