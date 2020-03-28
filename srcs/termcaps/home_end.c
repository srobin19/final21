#include "21sh.h"

/**
* end_enter change the position of the cursor to the end.
* @param {Structure t_termcaps} termcaps
*/

void	end_enter(t_termcaps *termcaps)
{
	int i;

	i = (termcaps->pos + termcaps->path) % termcaps->size;
	while ((termcaps->pos + termcaps->path) / termcaps->size <
  (termcaps->cmd_len + termcaps->path) / termcaps->size)
	{
		i = 0;
		tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
		termcaps->pos += termcaps->size;
	}
	while (i++ < (termcaps->cmd_len + termcaps->path) % termcaps->size)
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
	termcaps->pos = termcaps->cmd_len;
}

/**
* home_enter change the position of the cursor to the beginning.
* @param {Structure t_termcaps} termcaps
*/

void	home_enter(t_termcaps *termcaps, char **cmd)
{
	while ((termcaps->pos) / termcaps->size > 0)
	{
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		termcaps->pos -= termcaps->size;
	}
	while (termcaps->pos > 0)
		go_to_left(termcaps, cmd);
	while (termcaps->pos < 0)
		go_to_right(termcaps, cmd);
	termcaps->pos = 0;
}
