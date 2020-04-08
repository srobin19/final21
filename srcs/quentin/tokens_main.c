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

#include "21sh.h"
#include "q21sh.h"

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
	int	ret;

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

char	*get_var_name(char *curr_c)
{
	char *var_name;

	var_name = NULL;
	while (ft_isalpha(*curr_c) || ft_isdigit(*curr_c) || *curr_c == '_')
	{
		var_name = add_char_to_string(var_name, *curr_c);
		curr_c++;
	}
	return (var_name);
}

char	*replace_var(char *input, char **curr_c, char *var_name, char *var_val)
{
	char	*new;
	char	*new_ptr;
	char	*input_ptr;
	size_t	len;

	len = ft_strlen(input) - ft_strlen(var_name) + ft_strlen(var_val);
	if (!(new = malloc(len)))
		exit(EXIT_FAILURE);
	new_ptr = new;
	input_ptr = input;
	while (input_ptr != *curr_c)
		*(new_ptr++) = *(input_ptr++);
	*curr_c = new_ptr - 1;
	while (*var_val)
		*(new_ptr++) = *(var_val++);
	input_ptr += ft_strlen(var_name) + 1;
	while (*input_ptr)
		*(new_ptr++) = *(input_ptr++);
	*new_ptr = '\0';
	return(new);
}

char	*replace_tilde(char *input, char **curr_c, char *var_val)
{
	char	*new;
	char	*new_ptr;
	char	*input_ptr;
	size_t	len;

	len = ft_strlen(input) - 1 + ft_strlen(var_val);
	if (!(new = malloc(len)))
		exit(EXIT_FAILURE);
	new_ptr = new;
	input_ptr = input;
	while (input_ptr != *curr_c)
		*(new_ptr++) = *(input_ptr++);
	*curr_c = new_ptr - 1;
	while (*var_val)
		*(new_ptr++) = *(var_val++);
	input_ptr += 2;
	while (*input_ptr)
		*(new_ptr++) = *(input_ptr++);
	*new_ptr = '\0';
	return(new);
}

int	expand(char **curr_c, char **env, char **input)
{
	int	ret;
	char	*var_name;
	char	*var_val;

	ret = is_expandable(*curr_c, *input);
	if (ret == 1)
	{
		var_val = get_env_var(env, "HOME");
		*input = replace_tilde(*input, curr_c, var_val);
		free(var_val);
		return (1);
	}
	if (ret == 2)
	{
		var_name = get_var_name((*curr_c) + 1);
		var_val = get_env_var(env, var_name);
		*input = replace_var(*input, curr_c, var_name, var_val);
		free(var_name);
		free(var_val);
		return (1);
	}
	return (0);
}

static t_tokens	*get_tokens(char *input, t_tokens *toks, char **env)
{
	int		esc = 0;
	int		quoted = 0;
	int		word = 0;
	char		*curr_c = input;

	while (*curr_c)
	{
		if (update_inhibitors(&esc, &quoted, *curr_c))
			;
		else if (!esc && quoted != 1 && expand(&curr_c, env, &input))
			;
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

t_tokens		*lexer(char *input, char **env)
{
	t_tokens	*toks;

	if (!input)
		return (NULL);
	toks = NULL;
	toks = get_tokens(input, toks, env);
	toks = get_subtypes(toks);
	free(input);
	return (toks);
}
