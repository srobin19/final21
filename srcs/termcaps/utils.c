#include "21sh.h"

/*
** verif_backn
** @param {char} buffer
** @return integer true 1 false 0
*/
int		verif_backn(char *buffer)
{
	if ((buffer[1] == '\n' || !buffer[1]) && (buffer[2] == '\n' || !buffer[2]))
		return (1);
	return (0);
}

/*
** isprintable verify if all charactere into a string is printable
** @param {char} str
** @return integer true 1 false 0
*/
int		isprintable(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			if (str[i] != '\n')
				return (0);
	return (1);
}

/*
** trim_termcaps reçoit une string et retourne une copy de string
** qui as été trim.
** @params {char} line
** @return new trim string
*/
char	*trim_termcaps(char *line)
{
	char *tmp;

	if (!(tmp = ft_strtrim(line)))
		exit(-1);
	ft_strdel(&line);
	return (tmp);
}
