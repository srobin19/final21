#ifndef TERMCAPS_H
# define TERMCAPS_H
# define MAJ_LEFT ";2D"
# define MAJ_RIGHT ";2C"
# define MAJ_UP ";2A"
# define MAJ_DOWN ";2B"
# define COLOR_WHITE 7
# define COLOR_BLACK 0
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <fcntl.h>

enum					e_key_press
{
	KEY_NULL = 0,
	CTRL_C = 3,
	CTRL_D = 4,
	CTRL_R = 18,
	TAB = 9,
	ENTER = 10,
	ESC = 27,
	ARROW_1 = 27,
	ARROW_2 = 91,
	CTRL_MAJ_E_1 = -62,
	CTRL_MAJ_E_2 = -76,
	CTRL_MAJ_C_1 = -61,
	CTRL_MAJ_C_2 = -121,
	CTRL_MAJ_X_1 = -53,
	CTRL_MAJ_X_2 = -101,
	CTRL_MAJ_V_1 = -30,
	CTRL_MAJ_V_2 = -105,
	HOME = 72,
	END = 70,
	MAJ = 49,
	UP_ARROW = 66,
	DOWN_ARROW = 65,
	LEFT_ARROW = 68,
	RIGHT_ARROW = 67,
	BACKSPACE = 127,
	UP_ARR = 4283163,
	DOWN_ARR = 4348699,
	LEFT_ARR = 4479771,
	RIGHT_ARR = 4414235
};

typedef struct				s_history
{
	char					*opening;
	char					*closing;
	struct s_history		*next;
}							t_history;

typedef struct			s_termcaps
{
	char				*clearstr;
	char				*godown;
	char				*del_line;
	char				*del_allline;
	char				*gostart;
	char				*gotostr;
	char				*goleft;
	char				*goup;
	char				*goright;
	char				*curs_save;
	char				*curs_restore;
	struct termios		term;
	struct termios		term_restore;
	int					pos;
	size_t				history_pos;
	size_t				history_len;
	char				*last_cmd;
	int					cmd_len;
	int					cc_start;
	char				tmp_select[NAME_MAX];
	char				copy[NAME_MAX];
	int					edit_mode;
	char				*reset;
	char				*highlight_color;
	int					size;
	int					height;
	int					pos_height;
	int					display_option;
	char				*text_color;
	int					pos_line;
	int					path;
	int					prev_pos;
	int					prev_cmd;
	int					research_mode;
	size_t				r_hist;
	int					auto_start;
	int					auto_end;
	int					firt_arg;
	int					stop_quote;
  int         stdin_copy;
  int         i;
}						t_termcaps;

/*
** edition.c
*/
void	cut_into_cmd(t_termcaps *termcaps, char **cmd);
void	paste_into_cmd(t_termcaps *termcaps, char **cmd);

/*
** home_end.c
*/
void	end_enter(t_termcaps *termcaps);
void	home_enter(t_termcaps *termcaps, char **cmd);

/*
** init.c
*/
int		init_termcaps(t_termcaps *termcaps);
void	prepare_cmd(t_termcaps *termcaps, int display_prompt, char **cmd);

/*
** key.c
*/
char	*entre(t_termcaps *termcaps, char *cmd, char **buffer);
void	dispatch_key(char **buffer, char **cmd, t_termcaps **termcaps);

/*
** maj_key.c
*/
void	maj_combinate(t_termcaps *termcaps, char *cmd, char *buffer);
void	alt_maj_enter(t_termcaps *termcaps, char **cmd, char *buffer);

/*
** move.c
*/
void	go_down(t_termcaps *termcaps);
void	go_to_left(t_termcaps *termcaps, char **cmd);
void	go_to_right(t_termcaps *termcaps, char **cmd);
void	left_enter(t_termcaps *termcaps, char **cmd);
void	right_enter(t_termcaps *termcaps, char **cmd);

/*
** prompt.c
*/
void	choose_display(t_termcaps *termcaps);
int		display_name(void);

/*
** print_edition_mode.c
*/
void		print_highlight(t_termcaps *termcaps, char *cmd);

/*
** modify_command.c
*/
void			remove_backn(char **buffer);
void			remove_last_backn(char **buffer);
char			*remove_previous_char(char *str, t_termcaps *termcaps);
void			add_char_into_cmd(char **str, char *buff, t_termcaps *termcaps);
void			add_char_end(char **str, char *buff);

/*
** print_command.c
*/
void			print_new_cmd(char *cmd, t_termcaps *termcaps, int opt_save);

/*
** utils.c
*/
char	*trim_termcaps(char *line);
int		isprintable(char *str);
int		verif_backn(char *buffer);

/*
** termcaps_controler.c
*/
char			*core_termcaps(t_termcaps *termcaps, int display_prompt_options);

/*
** history.c
*/
int		open_history_file(t_termcaps *termcaps);
void	termcaps_histo(t_termcaps *termcaps, char **cmd, int i);
void	add_in_history(t_termcaps *termcaps, char *cmd);
#endif
