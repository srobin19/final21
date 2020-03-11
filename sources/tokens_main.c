/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:35:59 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:10:56 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void			fill_subtype(t_tokens *tok)
{
	if (!ft_strcmp(tok->string, ";"))
			tok->subtype = SMCL;
	if (!ft_strcmp(tok->string, "|"))
			tok->subtype = PIPE;
	if (ft_strchr(tok->string, '>') || ft_strchr(tok->string, '<'))
			tok->subtype = REDI;
}

t_tokens		*get_subtypes(t_tokens *toks)
{
	t_tokens	*curr_t;

	if (!toks)
		return (NULL);
	curr_t = toks;
	while (curr_t)
	{
		if (curr_t->type == OPER)
			fill_subtype(curr_t);
		curr_t = curr_t->next;
	}
	return (toks);
}

static int		update_quoted_state(int esc, int *quoted, char curr_c)
{
	int	tmp;
	int	ret;

	tmp = *quoted;
	ret = 1;
	if (esc != 1 && !(*quoted) && curr_c == '\'')
		*quoted = S_QUOTE;
	else if (esc != 1 && !(*quoted) && curr_c == '\"')
		*quoted = D_QUOTE;
	else if (*quoted == S_QUOTE && curr_c == '\'')
		*quoted = 0;
	else if (esc != 1 && *quoted == D_QUOTE && curr_c == '\"')
		*quoted = 0;
	else
		ret = 0;
	return (ret);
}

static int		update_escape_state(int *esc, int quoted, char curr_c)
{
	if (*esc != 1 && curr_c == '\\' && quoted != S_QUOTE)
	{
		*esc = 1;
		return (1);
	}
	else if (*esc == 1)
		*esc += 1;
	else
		*esc = 0;
	return (0);
}

static int		update_inhibitors(int *esc, int *quoted, char curr_c)
{
	if (update_quoted_state(*esc, quoted, curr_c))
		return (1);
	else if (update_escape_state(esc, *quoted, curr_c))
		return (1);
	else
		return (0);
}

static void		get_operator(char **curr_c, t_tokens *toks)
{
	char		*curr;
	t_tokens	*working_tok;

	toks = add_token_node(toks, **curr_c, OPER, 0);
	working_tok = last_node(toks);
	curr = *curr_c;
	curr++;
	while (is_part_operator(curr, curr - *curr_c))
	{
		add_char_to_token(working_tok, *curr);
		curr++;
	}
	*curr_c = curr - 1;
}

/*static int is_expandable(char *curr_c)
{
	if (*curr_c == '~' &&
			(curr_c[1] == 0 || ft_isblank(curr_c[1]) || curr_c[1] == '/'))
		return (1);
	if (*curr_c == '$' && curr_c[1] != '&')
		return (1);
	return (0);
}
*/
static t_tokens	*get_tokens(char *curr_c, t_tokens *toks)
{
	int		esc;
	int		quoted;
	int		word;

	esc = 0;
	quoted = 0;
	word = 0;
	while (*curr_c)
	{
		if (update_inhibitors(&esc, &quoted, *curr_c))
			;
//		else if (!esc && quoted != 1 && is_expandable(curr_c) && (!(word = 0)))
//			get_expanded(&curr_c, toks);
		else if (!esc && !quoted && is_operator(curr_c) && (!(word = 0)))
			get_operator(&curr_c, toks);
		else if (!esc && !quoted && is_blank_char(*curr_c))
			word = 0;
		else if (word)
			add_char_to_token(last_node(toks), *curr_c);
		else if ((word = 1))
			toks = add_token_node(toks, *curr_c, WORD, 0);
		curr_c++;
	}
	return (toks);
}

t_tokens		*lexer(char *input)
{
	t_tokens	*toks;

	if (!input)
		return (NULL);
	toks = NULL;
	toks = get_tokens(input, toks);
	toks = get_subtypes(toks);
	free(input);
	return (toks);
}
