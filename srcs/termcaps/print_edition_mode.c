#include "21sh.h"

/*
** highlight initialise the color of the text.
** @params {Structure t_termcaps}
*/

static void		highlight(t_termcaps *termcaps)
{
	ft_putstr(tparm(termcaps->highlight_color, COLOR_WHITE));
	ft_putstr(tparm(termcaps->text_color, COLOR_BLACK));
}

/*
** reset_highlight reset the text color
** @params {Structure t_termcaps}
*/
static void		reset_highlight(t_termcaps *termcaps)
{
	ft_putstr(termcaps->reset);
}

/*
** del_line del a line and reset the cursor.
** @params {Structure t_termcaps}
*/
static void		del_line(t_termcaps *termcaps)
{
	tputs(termcaps->curs_save, 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_line, 1, (void *)ft_putchar);
}

/*
** print_highlight del the command line display the prompt and rewrite the line
** with the select charactere. Change the textcolor. After that we reset the
** color and write the cmd selected
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/
void		print_highlight(t_termcaps *termcaps, char *cmd)
{
	int i;
	int y;

	i = 0;
	y = 0;
	del_line(termcaps);
	display_name();
	ft_bzero(termcaps->tmp_select, NAME_MAX);
	while (i < termcaps->cc_start && i < termcaps->pos)
		ft_putchar(cmd[i++]);
	highlight(termcaps);
	if (termcaps->cc_start == termcaps->pos)
	{
		reset_highlight(termcaps);
		ft_putstr(cmd + i);
		return ;
	}
	while (i < bigger(termcaps->cc_start, termcaps->pos))
	{
		termcaps->tmp_select[y++] = cmd[i];
		ft_putchar(cmd[i]);
		i++;
	}
	reset_highlight(termcaps);
	ft_putstr(cmd + i);
}
