/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:45:23 by qbackaer          #+#    #+#             */
/*   Updated: 2020/02/25 16:52:18 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "q21sh.h"

static char		*is_quote_closed(char *start)
{
	char	*end;
	int		esc;

	esc = 0;
	end = start + 1;
	while (*end)
	{
		if (!esc && *end == '\\')
		{
			esc = 1;
			end++;
			continue ;
		}
		if (*end == *start && (*start == '\'' || !esc))
			return (end);
		esc = 0;
		end++;
	}
	return (NULL);
}

static int		is_input_done(char *str)
{
	int			esc;
	char		*ptr;

	ptr = str;
	esc = 0;
	while (*ptr)
	{
		if (!esc && *ptr == '\\')
		{
			esc = 1;
			ptr++;
			continue ;
		}
		if (!esc && (*ptr == '\"' || *ptr == '\''))
			if (!(ptr = is_quote_closed(ptr)))
				return (0);
		if (!esc && *ptr == '|' && is_only_whitespaces(ptr + 1))
			return (0);
		esc = 0;
		ptr++;
	}
	if (ft_strlen(str) && *(ptr - 1) == '\\')
		return (0);
	return (1);
}

//This functions uses get_next_line to get a line from the user and then
//check if the input is done, that is to say if all quotes are closed
//(including no backslash at the end of the line)
static char		*get_all_lines(void)
{
	char		*full_input;
	char		*line;
	char		*temp;

	full_input = NULL;
	while (1)
	{
		if (get_next_line(0, &line, 1) < 0)
			exit(EXIT_FAILURE);
		temp = line;
		line = ft_strtrim(line);
		free(temp);
		temp = full_input;
		if (!(full_input = ft_strjoin(full_input, line)))
			exit(EXIT_FAILURE);
		free(temp);
		free(line);
		if (is_input_done(full_input))
			break ;
	}
	return (full_input);
}

//main function that gets user inputs using other functions then returns it
//as a string.
char			*get_input(void)
{
	char		*input;

	input = get_all_lines();
	if (!input || !ft_strlen(input))
		return (NULL);
	return (input);
}
