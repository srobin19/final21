#include "21sh.h"

/*
** win_change_handler malloc a structure of winsize
** and initialise the ioctl to have the controle for the mutiple line and save
** the result into the termcaps struct.
** @param {int} sig the signal
** @param {Structure t_termcaps} termcaps
*/

static void		win_change_handler(int sig, t_termcaps *termcaps)
{
	struct winsize *win_size;

	if (sig != SIGWINCH)
		return ;
	if (!(win_size = malloc(sizeof(struct winsize *))))
		return ;
	ioctl(0, TIOCGWINSZ, win_size);
	termcaps->size = win_size->ws_col;
	free(win_size);
}

/*
** ctrl_c we need to have free the command and the malloc a new adress to it.
** for the core_termcaps.
** after that the funciton reset the command (pos, cmd_len).
** And put the cursor to the good place
** @param {Structure t_termcaps} termcaps
** @param {char} cmd
*/

static void		ctrl_c(t_termcaps *termcaps, char **cmd)
{
	ft_strdel(cmd);
	if (!(*cmd = ft_strnew(0)))
		exit(-1);
	termcaps->pos = 0;
	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	termcaps->cmd_len = 0;
	ft_putstr("\n");
}

/*
** term_sig initialise the ioctl() function to have the controle when the line
** is to large to go under, after that the funciton check if the ctrl_c is
** actif.
** @param {char} cmd
** @param {Structure t_termcaps} termcaps
** @return a integer.
*/

static int		term_sig(char **cmd, t_termcaps *termcaps)
{
	win_change_handler(SIGWINCH, termcaps);
  if (g_shell->termcaps->i == 1)
		ctrl_c(termcaps, cmd);
	return (1);
}

/*
** core_termcaps read on the stdin file descriptor.
** It verify if there is active signal (ctrl_c). If there is no signal
** the function verify if the the last command was a ENTER
** If yes => we verify also if the line is not empty if the two condition are
** ok the function return the entre function
** If no we must to verify Wich key was enter. And after that the line is free
** and we begin a the pos 0 to have a new line.
** @param {Structure t_termcaps} termcaps
** @param {integer} display_prompt_options Option to display the prompt
** @return a command line.
*/

char			*core_termcaps(t_termcaps *termcaps, int display_prompt_options)
{
	char	*buffer;
	char	*cmd;

  cmd = ft_strnew(2);
  prepare_cmd(termcaps, display_prompt_options, &cmd);
	if (!(buffer = ft_strnew(3)))
		exit(-1);
	while (1)
	{
		if (cmd == NULL)
			if (!(cmd = ft_strnew(0)))
				exit(-1);
		read(0, buffer, 3);
    if (term_sig(&cmd, termcaps) == 0)
			return (NULL);
		if (buffer[0] == ENTER && verif_backn(buffer))
		{
				return (entre(termcaps, cmd, &buffer));
		}
		else
			dispatch_key(&buffer, &cmd, &termcaps);
		termcaps->prev_pos = termcaps->pos;
		ft_bzero(buffer, 3);
	}
}
