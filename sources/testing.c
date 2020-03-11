/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_tools_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:54 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 17:05:20 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void	display_ll(t_tokens *toks)
{
	t_tokens	*curr_t;
	int		n;

	if (!toks)
		return ;
	n = 0;
	curr_t = toks;
	while (curr_t)
	{
		printf("%d. ", n);
		if (curr_t->type == 1)
		{
			if (curr_t->subtype == 1)
				printf("{REDI}");
			if (curr_t->subtype == 2)
				printf("{PIPE}");
			if (curr_t->subtype == 3)
				printf("{SMCL}");
		}
		if (curr_t->type == 2)
			printf("(WORD)");
		printf(" [%s]\n", curr_t->string);
		curr_t = curr_t->next;
		n++;
	}
	printf("=================\n");
}
