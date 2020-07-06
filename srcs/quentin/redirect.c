/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:53:18 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:37:15 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

static int	is_only_digits(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	get_left_fd(char **curr_c)
{
	int fd;

	if (**curr_c == '>')
		fd = 1;
	else if (**curr_c == '<')
		fd = 0;
	else
	{
		fd = **curr_c - 48;
		*curr_c += 1;
	}
	return (fd);
}

static int	get_right_fd(char *r_value, char *curr_c)
{
	int fd;

	fd = -1;
	if (*curr_c == '>' && *(curr_c + 1 ) == '\0')
		fd = open(r_value, O_WRONLY|O_CREAT, 0666);
	else if (*curr_c == '>' && *(curr_c + 1) == '>')
		fd = open(r_value, O_WRONLY|O_CREAT|O_APPEND, 0666);
	else if (*curr_c == '<' && *(curr_c + 1) == '\0')
		fd = open(r_value, O_RDONLY|O_CREAT, 0666);
	else if ((*curr_c == '<' || *curr_c == '>') && *(curr_c + 1) == '&')
	{
		if (!ft_strcmp(r_value, "-"))
			return (-2);
		else if (is_only_digits(r_value))
			fd = ft_atoi(r_value);
		else
			return (-1);
	}
	else
		return (-1);
	return (fd);
}
 void	reset_redirections(t_dupsave *track)
{
	t_dupsave	*curr;

	if (!track)
		return ;
	curr = track;
	while (curr)
	{
		dup2(curr->fd_save, curr->fd_l);
		close(curr->fd_save);
		curr = curr->next;
	}
}

static void	apply_redirection(t_tokens *pnode, t_dupsave *track)
{
	int	fd_l;
	int	fd_r;
	int	fd_save;
	char	*curr_c;

	printf("apply_redirection IN\n");
	if (pnode->next == NULL)
	{
		ft_putendl_fd("redirection error: missing R_VALUE", 2);
		return ;
	}
	printf("pnode string: %s\n", pnode->string);
	curr_c = pnode->string;
	fd_l = get_left_fd(&curr_c);
	if ((fd_r = get_right_fd(pnode->next->string, curr_c)) == -1)
		return ;
	if (fd_r == -2)
		close(fd_l);
	else
	{
		fd_save = dup(fd_l);
		dup2(fd_r, fd_l);
		add_track_node(track, fd_l, fd_save);
	}
}

t_dupsave	*redirect(t_tokens *pnode)
{
	t_tokens *curr_tok;
	t_dupsave *track;

	curr_tok = pnode;
	track = NULL;
	while (curr_tok)
	{
		printf("TOKEN: %s\n", curr_tok->string);
		if (curr_tok->subtype == REDI)
			apply_redirection(curr_tok, track);
		curr_tok = curr_tok->next;
	}
	return (track);
}
