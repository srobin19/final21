#include "21sh.h"

/*
** read_last_line open the history file and read the line before the position
** @param {int} pos
** @return the line
*/
static char	*read_last_line(int pos)
{
	char	*line;
	int		i;
	int		fd;
	char	*history_path;

	i = 0;
	line = NULL;
	if (!(history_path = ft_strjoin(getenv("HOME"), "/.21sh_history")))
		exit(-1);
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
	{
		ft_strdel(&history_path);
		return (NULL);
	}
	ft_strdel(&history_path);
	get_next_line(fd, &line, 1);
	while ((i <= pos))
	{
		i++;
		ft_strdel(&line);
		get_next_line(fd, &line, 0);
	}
	close(fd);
	return (line);
}

/*
** termcaps_histo get the line into the history and print the line
** @param {int} i
** @param {char} cmd
** @param {Structure t_termcaps} termcaps
*/
void	termcaps_histo(t_termcaps *termcaps, char **cmd, int i)
{
	termcaps->edit_mode = FALSE;
	if (termcaps->history_pos < termcaps->history_len && i == 65)
	{
		termcaps->history_pos++;
		ft_strdel(cmd);
		*cmd = read_last_line(termcaps->history_len - termcaps->history_pos);
		print_new_cmd(*cmd, termcaps, 0);
	}
	else if (termcaps->history_pos > 1 && i == 66)
	{
		termcaps->history_pos--;
		ft_strdel(cmd);
		*cmd = read_last_line(termcaps->history_len - termcaps->history_pos);
		print_new_cmd(*cmd, termcaps, 0);
	}
	else if (termcaps->history_pos == 1 && i == 66)
	{
		termcaps->history_pos--;
		ft_strdel(cmd);
		*cmd = ft_strdup("");
		print_new_cmd(*cmd, termcaps, 0);
	}
	termcaps->cmd_len = (*cmd == NULL ? 0 : ft_strlen(*cmd));
	termcaps->pos = (*cmd == NULL ? 0 : ft_strlen(*cmd));
}

void	add_in_history(t_termcaps *termcaps, char *cmd)
{
	char	*cmd2;
	char	*history_path;
	int		fd;

	if (cmd[0] == '\0' || (ft_strcmp(termcaps->last_cmd, cmd) == 0))
		return ;
	if (!(history_path = ft_strjoin(getenv("HOME"), "/.21sh_history")))
		exit(-1);
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
	{
		ft_strdel(&history_path);
		return ;
	}
	ft_strdel(&history_path);
	if (!(cmd2 = ft_strjoin(cmd, "\n")))
		exit(-1);
	write(fd, cmd2, ft_strlen(cmd2));
	termcaps->history_len++;
	termcaps->history_pos++;
	ft_strdel(&termcaps->last_cmd);
	termcaps->last_cmd = ft_strdup(cmd);
	ft_strdel(&cmd2);
	close(fd);
}

/*
** open_history_file open or create the history file. Read all line into the
** the file and set the termcaps history element.
** @param {Structure t_termcaps} termcaps
** @return interger 1 success 0 failure
*/
int		open_history_file(t_termcaps *termcaps)
{
	char	*history_path;
	char	*line;
	int		fd;

	line = NULL;
	history_path = ft_strjoin(getenv("HOME"), "/.21sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
		return (-1);
	ft_strdel(&history_path);
	termcaps->history_len = 0;
	termcaps->last_cmd = ft_strnew(0);
	while (get_next_line(fd, &line, 0))
	{
		ft_strdel(&termcaps->last_cmd);
		termcaps->history_len++;
		termcaps->last_cmd = ft_strdup(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (1);
}
