#ifndef SH21_H
# define SH21_H

# define SHELL_NAME "21SH"
# define DEFAULT_TEXT_EDITOR "vim"
# include <term.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include "termcaps.h"
# include "q21sh.h"
# include "../libft/libft.h"

typedef struct				s_shell
{
	t_termcaps				*termcaps;
}							t_shell;

extern t_shell				*g_shell;

#endif
