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

#include "21sh.h"
#include "q21sh.h"

t_dupsave	*add_track_node(t_dupsave *list, int fdl, int fdsave)
{
	t_dupsave *node;
	t_dupsave *roam;

	if (!(node = malloc(sizeof(t_dupsave))))
		exit(EXIT_FAILURE);
	node->fd_l = fdl;
	node->fd_save = fdsave;
	node->next = NULL;
	if (!list)
		return (node);
	roam = list;
	while (roam->next)
		roam = roam->next;
	roam->next = node;
	return (list);
}
