#include "21sh.h"

/*
** term_reset reset the termcaps after a command.
** @params {Structure t_termcaps} termcaps
*/
static void			reset_termcaps(t_termcaps *termcaps)
{
	int x;
	int y;
	int i;
	int	height;

	i = 0;
	y = ((termcaps->pos + termcaps->path) / termcaps->size);
	x = (termcaps->pos + termcaps->path) % termcaps->size;
	height = ((termcaps->cmd_len + termcaps->path) / termcaps->size);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	while (i < (height - y))
	{
		i++;
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	}
	i = 0;
	while (i < x)
	{
		i++;
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
	}
}

/*
** no_print is call just before to print the new command. The function set
** some element of the termcaps
** @params {int} height
** @params {Structure t_termcaps} termcaps
*/
static void		no_print(int *height, t_termcaps *termcaps)
{
	int		y;

	y = ((termcaps->prev_pos + termcaps->path) / termcaps->size);
	*height = ((termcaps->cmd_len + termcaps->path) / termcaps->size);
	while (y-- > 0)
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_allline, 1, (void *)ft_putchar);
}

/*
** print_new_cmd 'reset' some element of termcaps to print one line by line.
** chose the correct display and after that print the command.
** @param {Structure t_termcaps} termcaps
** @param {int} opt_save
** @param {char} cmd
*/
void		print_new_cmd(char *cmd, t_termcaps *termcaps, int opt_save)
{
	int		height;

  no_print(&height, termcaps);
  choose_display(termcaps);
	if (termcaps->edit_mode == 1)
		print_highlight(termcaps, cmd);
  else
    ft_putstr(cmd);
	termcaps->height = height;
	if ((termcaps->cmd_len + termcaps->path) % termcaps->size == 0)
		tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	if (opt_save != 0)
		reset_termcaps(termcaps);
	termcaps->prev_pos = termcaps->pos;
}
