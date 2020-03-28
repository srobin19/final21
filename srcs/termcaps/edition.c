#include "21sh.h"

/*
** cut cut into a command
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/

static void		cut(t_termcaps *termcaps, char **cmd)
{
	char	*tmp;
	char	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	tmp = *cmd;
	new = ft_strnew(ft_strlen(*cmd) - val_abs(termcaps->cc_start -
		termcaps->pos));
	while ((tmp[y]) && (i < smaller(termcaps->cc_start, termcaps->pos)) && i <
		(int)ft_strlen(*cmd))
		new[i++] = tmp[y++];
	y = bigger(termcaps->cc_start, termcaps->pos);
	while (tmp[y])
		new[i++] = tmp[y++];
	ft_strdel(cmd);
	*cmd = ft_strdup(new);
	ft_strdel(&new);
}

/*
** cut_into_cmd this function cut into a command. Put the Edit mode to
** FALSE and print the new command
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/

void	cut_into_cmd(t_termcaps *termcaps, char **cmd)
{
	if (termcaps->edit_mode)
	{
		cut(termcaps, cmd);
		ft_strcpy(termcaps->copy, termcaps->tmp_select);
		termcaps->edit_mode = FALSE;
		if (termcaps->cc_start < termcaps->pos)
			termcaps->pos -= ft_strlen(termcaps->copy);
		termcaps->cmd_len -= ft_strlen(termcaps->tmp_select);
		print_new_cmd(*cmd, termcaps, 1);
	}
}

/*
** paste_into_cmd this function paste a string into a command. It will add
** all of char of this string into the old string. and print the new string
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/

void	paste_into_cmd(t_termcaps *termcaps, char **cmd)
{
	if (termcaps->copy[0])
	{
		add_char_into_cmd(cmd, termcaps->copy, termcaps);
		termcaps->pos += ft_strlen(termcaps->copy);
		termcaps->cmd_len += ft_strlen(termcaps->copy);
		print_new_cmd(*cmd, termcaps, 1);
		termcaps->edit_mode = FALSE;
	}
}
