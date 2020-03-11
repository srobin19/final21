/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:31:29 by qbackaer          #+#    #+#             */
/*   Updated: 2020/01/09 17:31:25 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static void		prompt_path(void)
{
	char	cwd_buff[PATH_MAX + 1];
	int		i;

	getcwd(cwd_buff, PATH_MAX + 1);
	i = 0;
	while (cwd_buff[i])
	{
		if (cwd_buff[i] != '/')
		{
			ft_putstr(RESET);
			ft_putchar(cwd_buff[i++]);
		}
		else
		{
			ft_putstr(MAG);
			ft_putchar(cwd_buff[i++]);
		}
	}
}

void			printenv(char **env)
{
	char	**roam;

	if (!env)
	{
		ft_putendl_fd("21sh: error: empty environement.", 2);
		return ;
	}
	roam = env;
	while (*roam)
	{
		ft_putendl(*roam);
		roam++;
	}
}

void			prompt(void)
{
	ft_putstr(CYAN);
	ft_putstr("@");
	prompt_path();
	ft_putstr(MAG);
	ft_putstr("➠➤ ");
	ft_putstr(RESET);
}

void			title(void)
{
	ft_putstr("-------------------\n|");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr("  21SH  ");
	ft_putstr(CYAN);
	ft_putstr("0.0.1  ");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr("|\n-------------------\n");
	ft_putstr("developped by ➠\t");
	ft_putstr(CYAN);
	ft_putstr("qbackaer@student.s19.be\n");
	ft_putstr("\t\tsrobin@student.s19.be\n\n");
	ft_putstr(CYAN);
	ft_putstr(CYAN);
	ft_putstr(RESET);
	ft_putstr("GNU GENERAL PUBLIC LICENSE\n");
	ft_putstr("Version 3, 29 June 2007\n\n\n");
}
