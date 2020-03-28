#include "21sh.h"

/*
** just_char_enter add the new charactere at end of the command line and print
** the new command line
** @param {char} cmd
** @param {char} buffer
** @param {Structure t_termcaps} termcaps
*/

static void			just_char_enter(t_termcaps **termcaps, char **cmd, char **buffer)
{
	(*termcaps)->edit_mode = FALSE;
	((*termcaps)->pos == (int)ft_strlen(*cmd)) ?
	add_char_end(cmd, *buffer) : add_char_into_cmd(cmd, *buffer, *termcaps);
	(*termcaps)->pos += ft_strlen(*buffer);
	(*termcaps)->cmd_len += ft_strlen(*buffer);
	print_new_cmd(*cmd, *termcaps, 1);
}

/*
** arrow_enter find wich arrow was enter if is not a arrow so we must to check
** if is a HOME/END/Maj.
** @param {char} cmd
** @param {char} buffer
** @param {Structure t_termcaps} termcaps
*/

static void	arrow_enter(char *buffer, t_termcaps *termcaps, char **cmd)
{
	if (buffer[2] == LEFT_ARROW && termcaps->pos > 0)
		left_enter(termcaps, cmd);
	else if (buffer[2] == RIGHT_ARROW && termcaps->pos < termcaps->cmd_len)
		right_enter(termcaps, cmd);
	else if (buffer[2] == UP_ARROW || buffer[2] == DOWN_ARROW)
		termcaps_histo(termcaps, cmd, buffer[2]);
	else if (buffer[2] == HOME)
		home_enter(termcaps, cmd);
  else if (buffer[2] == END)
		end_enter(termcaps);
	else if (buffer[2] == MAJ)
		maj_combinate(termcaps, *cmd, buffer);
}

/*
** entre put the edit_mode to false free the buffer and add into the history
** the new command. After that the function reset the cursor.
** @param {Structure t_termcaps} termcaps
** @param {char} buffer
** @param {char} cmd
** @return the command line
*/

char	*entre(t_termcaps *termcaps, char *cmd, char **buffer)
{
	termcaps->edit_mode = FALSE;
	ft_strdel(buffer);
	add_in_history(termcaps, cmd);
	tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	if (tcsetattr(0, TCSADRAIN, &termcaps->term_restore) == -1)
		exit(-1);
	return (cmd);
}

/*
** backspace_enter remove the charactere that we would like to remove. And
** print the new command line
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/

static void	backspace_enter(char **cmd, t_termcaps *termcaps)
{
	termcaps->edit_mode = FALSE;
	if (termcaps->pos > 0)
	{
		*cmd = remove_previous_char(*cmd, termcaps);
		termcaps->pos--;
		termcaps->cmd_len--;
		print_new_cmd(*cmd, termcaps, 2);
	}
}

/*
** dispatch_key find wich key was enter. Before that we must to clean the
** buffer (Key) if any key is found we need just to print the charactere
** @param {Structure t_termcaps} termcaps
** @param {char} buffer
** @param {char} cmd
*/

void			dispatch_key(char **buffer, char **cmd, t_termcaps **termcaps)
{
	remove_backn(buffer);
	remove_last_backn(buffer);
	if ((*buffer)[0] == CTRL_D && *cmd[0] == '\0')
	{
		tcsetattr(0, 0, &(*termcaps)->term_restore);
		exit(0);
	}
	if ((*buffer)[0] == ARROW_1 && (*buffer)[1] == ARROW_2)
		arrow_enter(*buffer, *termcaps, cmd);
	else if ((*buffer)[0] == BACKSPACE)
		backspace_enter(cmd, *termcaps);
  else if ((*buffer)[0] == -62 || (*buffer)[0] == -61 || (*buffer)[0] == -53
	|| (*buffer)[0] == -30)
		alt_maj_enter(*termcaps, cmd, *buffer);
	else if (isprintable(*buffer) || (*buffer)[0] == '\n')
		just_char_enter(termcaps, cmd, buffer);
}
