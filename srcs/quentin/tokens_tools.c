/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:36:09 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:13:05 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

int			is_blank_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int			is_operator(char *c)
{
	if (*c == '|' || *c == ';' || *c == '<' || *c == '>')
		return (1);
	if (ft_isdigit(*c) && (*(c + 1) == '<' || *(c + 1) == '>'))
		return (1);
	return (0);
}

char		*ctos(char c)
{
	char *str;

	if (!(str = malloc(2)))
		exit(EXIT_FAILURE);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char		*add_char_to_string(char *str, char c)
{
	char	*new_str;
	char	*new_ptr;
	char	*org_ptr;

	if (!(new_str = malloc(ft_strlen(str) + 2)))
		exit(EXIT_FAILURE);
	new_ptr = new_str;
	org_ptr = str;
	while (org_ptr && *org_ptr != '\0')
		*(new_ptr++) = *(org_ptr++);
	*(new_ptr++) = c;
	*new_ptr = '\0';
	if (str)
		free(str);
	return (new_str);
}

void		add_char_to_token(t_tokens *tok, char c)
{
	char	*new_str;
	char	*org_ptr;
	char	*new_ptr;

	if (!(new_str = malloc(ft_strlen(tok->string) + 2)))
		exit(EXIT_FAILURE);
	org_ptr = tok->string;
	new_ptr = new_str;
	while (org_ptr && *org_ptr != '\0')
		*(new_ptr++) = *(org_ptr++);
	*(new_ptr++) = c;
	*new_ptr = '\0';
	if (tok->string)
		free(tok->string);
	tok->string = new_str;
}

int			is_part_operator(char *curr_c, int op)
{
	if (op == 1 && ft_isdigit(*(curr_c - 1))
			&& (*curr_c == '<' || *curr_c == '>'))
		return (1);
	if ((op == 1 || op == 2) && (*(curr_c - 1) == '<' || *(curr_c - 1) == '>')
			&& (*(curr_c - 1) == *curr_c || *curr_c == '&'))
		return (1);
	if (op > 2 && (*curr_c == '<' || *curr_c == '>'))
		return (-1);
	else
		return (0);
}

int is_expandable(char *curr_c, char *input)
{
	int ret;

	ret = 0;
	if (curr_c[0] == '~')
	{
		if (curr_c[1] == 0 || is_blank_char(curr_c[1]) || curr_c[1] == '/')
			ret = 1;
		if (curr_c > input)
			if (!(is_blank_char(curr_c[-1]) || curr_c[-1] == '/'))
				ret = 0;
	}
	if (curr_c[0] == '$' && curr_c[1] != '$')
		ret = 2;
	return (ret);
}
