/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_gather.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:49:52 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:59:22 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char			**gather_cmds_tokens(t_tokens *cmd_group)
{
	char		**full_cmd = NULL;
	t_tokens	*curr = cmd_group;
	int		redir = 0;;

	if (!cmd_group)
		return (NULL);
	while (curr)
	{
		if (curr->subtype == REDI)
			redir = 1;
		if (!redir && curr->type == WORD)
			full_cmd = ft_realloc_tab(full_cmd, curr->string);
		if (redir && curr->type == WORD)
			redir = 0;
		curr = curr->next;
	}
	return (full_cmd);
}
