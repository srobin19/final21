#include "21sh.h"

/*
** go_down move the cursor downward
** @param {Structure t_termcaps}
*/

void	go_down(t_termcaps *termcaps)
{
	int i;

	i = 0;
	tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	while (i < (termcaps->pos + termcaps->path) % termcaps->size)
	{
		i++;
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
	}
	termcaps->pos = termcaps->pos + termcaps->size;
}

/*
** go_to_left move the cursor leftward and if the Edit mode is enable print the
** command with highlight
** @param {Structure t_termcaps}
** @param {char} cmd
*/

void	go_to_left(t_termcaps *termcaps, char **cmd)
{
	termcaps->pos--;
	if (termcaps->edit_mode)
		print_new_cmd(*cmd, termcaps, 1);
	else
		tputs(tgoto(termcaps->goleft, 0, 0), 1, (void *)ft_putchar);
}

/*
** go_to_right move the cursor rigthward and if the Edit mode is enable print
** the command with highlight
** @param {Structure t_termcaps}
** @param {char} cmd
*/

void	go_to_right(t_termcaps *termcaps, char **cmd)
{
	termcaps->pos++;
	if (termcaps->edit_mode)
		print_new_cmd(*cmd, termcaps, 1);
	else
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
}

/*
** left_enter verify if the command line is not the large. If is it we change
** the position of the cursor and go to the line.
** @param {Structure t_termcaps}
** @param {char} cmd
*/

void	left_enter(t_termcaps *termcaps, char **cmd)
{
	int i;

	i = -1;
	if ((termcaps->pos + termcaps->path) % termcaps->size == 0)
	{
		termcaps->pos--;
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		while (i++ < termcaps->size)
			tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
	}
	else
		go_to_left(termcaps, cmd);
}

/*
** right_enter verify if the command line is not the large. If is it we change
** the position of the cursor and move a line.
** @param {Structure t_termcaps}
** @param {char} cmd
*/

void	right_enter(t_termcaps *termcaps, char **cmd)
{
	if (((termcaps->pos + termcaps->path) % termcaps->size) >= termcaps->size - 1)
	{
		termcaps->pos++;
		tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	}
	else
		go_to_right(termcaps, cmd);
}
