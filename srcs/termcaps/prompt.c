#include "21sh.h"

/*
** get_dirpath this function get the pwd.
** @return the path where the user is located
*/

static char		*get_dirpath(void)
{
	char *path;
	char *dir;

	if ((path = getcwd(NULL, 0)) == NULL)
		return (ft_strdup(""));
	if ((dir = ft_strdup(strrchr(path, '/') + 1)) == NULL)
		exit(EXIT_FAILURE);
	if (ft_strequ(dir, ""))
	{
		ft_strdel(&dir);
		if ((dir = ft_strdup("/")) == NULL)
			exit(EXIT_FAILURE);
	}
	ft_strdel(&path);
	return (dir);
}

/*
** display_name
** @return the custome path where the user is located
*/

int		display_name(void)
{
	char	*dir;
	int		len_dir;

	if (!(dir = get_dirpath()))
		exit(-1);
	len_dir = ft_strlen(dir);
	ft_putstr("\033[1m");
	ft_putstr(dir);
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	ft_putstr("\033[22m");
	ft_strdel(&dir);
	return (len_dir + 3);
}

/*
** only_arrow print a custome prompt for the double quote, or for heredocs,...
** return the len of the prompt
*/

static int		only_arrow(void)
{
	ft_putstr("\033[1m");
	ft_putstr("\033[37m");
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	ft_putstr("\033[22m");
	return (3);
}

/*
** choose_display check the display_option and dispatch the good prompt
** @param {Structure t_termcaps} termcaps
*/

void	choose_display(t_termcaps *termcaps)
{
	if (termcaps->display_option == 1)
		termcaps->path = display_name();
	else if (termcaps->display_option == 2)
		termcaps->path = only_arrow();
}
