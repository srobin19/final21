#include "21sh.h"

/*
** maj_right
** @param {Structure t_termcaps}
** @param {char} cmd
*/

static void	maj_right(t_termcaps *termcaps, char *cmd)
{
	while (cmd[termcaps->pos] == ' ' && termcaps->pos < (int)termcaps->cmd_len)
	{
		go_to_right(termcaps, &cmd);
		if ((termcaps->pos + termcaps->path) % termcaps->size == 0)
			tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	}
	while (cmd[termcaps->pos] != ' ' && termcaps->pos < (int)termcaps->cmd_len)
	{
		go_to_right(termcaps, &cmd);
		if ((termcaps->pos + termcaps->path) % termcaps->size == 0)
			tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	}
}

/*
** maj_combinate find wich key is combinate and dispatch the action
** @param {Structure t_termcaps}
** @param {char} cmd
** @param {char} buffer
*/

void	maj_combinate(t_termcaps *termcaps, char *cmd, char *buffer)
{
	read(0, buffer, 3);
	if (!ft_strcmp(buffer, MAJ_LEFT) && termcaps->pos > 0)
	{
		while (cmd[termcaps->pos] == ' ' && termcaps->pos > 0)
			go_to_left(termcaps, &cmd);
		while (cmd[termcaps->pos] != ' ' && termcaps->pos > 0)
			go_to_left(termcaps, &cmd);
	}
	else if (!ft_strcmp(buffer, MAJ_RIGHT))
		maj_right(termcaps, cmd);
	else if (!ft_strcmp(buffer, MAJ_UP) && termcaps->pos - termcaps->size > 0)
	{
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		termcaps->pos = termcaps->pos - termcaps->size;
	}
	else if (!ft_strcmp(buffer, MAJ_DOWN) && termcaps->pos + termcaps->size <
  termcaps->cmd_len)
		go_down(termcaps);
}

/*
** alt_maj_enter check the sequence and dispatch the associated action
** @param {Structure t_termcaps}
** @param {char} cmd
** @param {char} buffer
*/

void	alt_maj_enter(t_termcaps *termcaps, char **cmd, char *buffer)
{
	if (buffer[0] == CTRL_MAJ_E_1 && buffer[1] == CTRL_MAJ_E_2)
	{
		ft_bzero(termcaps->tmp_select, NAME_MAX);
		termcaps->cc_start = 0;
		termcaps->cc_start = termcaps->pos;
		termcaps->edit_mode = !termcaps->edit_mode;
		print_new_cmd(*cmd, termcaps, 1);
	}
	else if (buffer[0] == CTRL_MAJ_C_1 && buffer[1] == CTRL_MAJ_C_2)
	{
		if (termcaps->edit_mode)
		{
			ft_bzero(termcaps->copy, NAME_MAX);
			ft_strcpy(termcaps->copy, termcaps->tmp_select);
			termcaps->edit_mode = !termcaps->edit_mode;
			print_new_cmd(*cmd, termcaps, 1);
		}
	}
	else if (buffer[0] == CTRL_MAJ_X_1 && buffer[1] == CTRL_MAJ_X_2)
		cut_into_cmd(termcaps, cmd);
	else if (buffer[0] == CTRL_MAJ_V_1 && buffer[1] == CTRL_MAJ_V_2)
		paste_into_cmd(termcaps, cmd);
}
