/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:13:03 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 15:51:20 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static size_t	get_groups_number(t_tokens *toks, int splitter)
{
	t_tokens	*curr;
	size_t		n;

	curr = toks;
	n = 1;
	while (curr)
	{
		if (curr->subtype == splitter && curr->next)
			n++;
		curr = curr->next;
	}
	return (n);
}

static t_tokens	**init_tokens_groups(size_t size)
{
	t_tokens **toks_groups;

	if (!(toks_groups = malloc(sizeof(toks_groups) * size + 1)))
		exit(EXIT_FAILURE);
	while (size + 1)
	{
		toks_groups[size] = NULL;
		size--;
	}
	return (toks_groups);
}

void		display_split(t_tokens **toks_grp)
{
	t_tokens **curr;

	if (!toks_grp)
		return ;
	curr = toks_grp;
	while (*curr)
	{
		display_ll(*curr);
		curr++;
	}
	return ;
}

t_tokens		**split_tokens(t_tokens *toks_all, int splitter)
{
	t_tokens	**toks_groups;
	t_tokens	*curr_tok;
	t_tokens	**curr_grp;

	if (!toks_all)
		return (NULL);
	toks_groups = init_tokens_groups(get_groups_number(toks_all, splitter));
	curr_tok = toks_all;
	curr_grp = toks_groups;
	while (curr_tok)
	{
		if (curr_tok->subtype != splitter)
			*curr_grp = add_token_node_str
				(*curr_grp, curr_tok->string, 
				 curr_tok->type, curr_tok->subtype);
		else if (curr_grp++)
			while(curr_tok->next->subtype == splitter)
				curr_tok = curr_tok->next;
		curr_tok = curr_tok->next;
	}
	free_token_list(toks_all);
	return (toks_groups);
}
