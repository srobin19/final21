#include "21sh.h"

/*
** add_char_end add new charactere at the end of the command line
** @params {char} str
** @params {char} buff
*/
void		add_char_end(char **str, char *buff)
{
	char	*new;

	if (!(new = ft_strjoin(*str, buff)))
		exit(-1);
	ft_strdel(str);
	*str = ft_strdup(new);
	ft_strdel(&new);
}

/*
** add_char_into_cmd add new charactere into the command line
** @params {char} str
** @params {char} buff
** @params {Structure t_termcaps} termcaps
*/
void		add_char_into_cmd(char **str, char *buff, t_termcaps *termcaps)
{
	int		i;
	int		j;
	char	*temp;
	char	*new;
	char	*tmp2;

	i = 0;
	j = -1;
	tmp2 = *str;
	if (!(temp = ft_strnew((ft_strlen(*str) + ft_strlen(buff)))))
		exit(1);
	while (i < termcaps->pos)
	{
		temp[i++] = **str;
		(*str)++;
	}
	while (buff[++j])
		temp[i++] = buff[j];
	if (!(new = ft_strjoin(temp, *str)))
		exit(1);
	ft_strdel(&temp);
	ft_strdel(&tmp2);
	*str = ft_strdup(new);
	ft_strdel(&new);
}

/*
** remove_previous_char remove a charactere into the command line
** @params {char} str
** @params {Structure t_termcaps} termcaps
** @return the new command line
*/
char		*remove_previous_char(char *str, t_termcaps *termcaps)
{
	char	*new;
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	if (termcaps->cmd_len == 0 || termcaps->pos == 0)
		return (str);
	new = ft_strnew(termcaps->cmd_len);
	while (i < termcaps->pos - 1)
	{
		new[i++] = *str;
		str++;
	}
	str++;
	new = ft_strjoin_free(&new, &str, 0);
	ft_strdel(&tmp);
	return (new);
}

/*
** remove_last_backn remove the last \n of a string
** @params {char} buffer
*/
void			remove_last_backn(char **buffer)
{
	int			i;
	int			len;
	char		*tmp;

	i = 0;
	len = 0;
	tmp = ft_strnew(ft_strlen(*buffer));
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == '\n')
		{
			tmp[len] = ' ';
			len++;
		}
		else
		{
			tmp[len] = (*buffer)[i];
			len++;
		}
		i++;
	}
	ft_strdel(buffer);
	*buffer = ft_strdup(tmp);
	ft_strdel(&tmp);
}

/*
** remove_backn remove all \n of a string
** @params {char} buffer
*/
void			remove_backn(char **buffer)
{
	int			i;
	int			len;
	char		*tmp;

	i = 0;
	len = 0;
	while ((*buffer)[i] && (*buffer)[i] == '\n')
		i++;
	tmp = ft_strnew(ft_strlen(*buffer));
	while ((*buffer)[i])
	{
		tmp[len] = (*buffer)[i];
		i++;
		len++;
	}
	ft_strdel(buffer);
	*buffer = ft_strdup(tmp);
	ft_strdel(&tmp);
}
