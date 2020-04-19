/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:30:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 18:06:02 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"


int	echo(char **cmd)
{
	char	**ptr;
	int	final_nl;

	ptr = cmd + 1;
	final_nl = 1;
	if (!ft_strcmp(*ptr, "-n"))
	{
		final_nl = 0;
		cmd++;
	}
	while (*ptr)
	{
		ft_putstr(*ptr);
		ft_putchar(' ');
		ptr++;
	}
	if (final_nl)
		ft_putchar('\n');
	return (0);
}
