/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:20:51 by qbackaer          #+#    #+#             */
/*   Updated: 2020/03/09 19:15:38 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOSH_H
# define TOSH_H

# define S_QUOTE 1
# define D_QUOTE 2

# define MAG "\x1B[35m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"
# define SHELL_NAME "21SH"
# define DEFAULT_TEXT_EDITOR "vim"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "termcaps.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <term.h>
# include "termcaps.h"

//type
# define OPER 1
# define WORD 2
//subtype
# define REDI 1
# define PIPE 2
# define SMCL 3
typedef struct	s_tokens
{
	int			type;
	int			subtype;
	char			*string;
	struct s_tokens		*next;

}		t_tokens;

typedef struct				s_shell
{
	t_termcaps				*termcaps;
}							t_shell;

extern t_shell				*g_shell;

/*
** display.c
*/
void		printenv(char **env);
void		prompt(void);
void		title(void);

/*
** execute_main.c
*/

/*
** input_main.c
*/
char		*get_input(void);
/*
** input_tools.c
*/
int			is_only_whitespaces(char *str);

/*
** redirect_apply.c
*/
int			apply_output_redir
			(char *operand, char *l_value, char *r_value);
int			apply_input_redir
			(char *operand, char *l_value, char *r_value);
/*
** redirect_parse.c
*/
void		redirect(t_tokens *pnode);

/*
** tokens_gather.c
*/
char 		**gather_cmds_tokens(t_tokens *group);
t_tokens	*gather_redir_tokens(t_tokens *group);

/*
** tokens_list.c
*/
t_tokens	*add_token_node(t_tokens *list, char fc, int tp, int sub);
t_tokens	*add_token_node_str(t_tokens *list, char *str, int tp, int sub);
void		free_token_list(t_tokens *list);
size_t		count_nodes(t_tokens *list);
void		free_token_group(t_tokens **list);
t_tokens	*last_node(t_tokens *toks);

/*
** tokens_main.c
*/
t_tokens	*lexer(char *input);

/*
** tokens_get.c
*/
int			is_blank_char(char c);
int			is_operator(char *c);
int			is_part_operator(char *curr_c, int op);
char		*ctos(char c);
void		add_char_to_token(t_tokens *tok, char c);

/*
** tokens_split.c
*/
t_tokens	**split_tokens(t_tokens *toks, int splitter);
void		display_split(t_tokens **toks_grp);

/*
** tokens_tools_a.c
*/
int			is_redirection(char *ptr);
int			is_quote(char *ptr);
int			get_dquote_len(char *start);
int			get_squote_len(char *start);
int			is_special(char *c);

/*
** tokens_tools_b.c
*/
char		*add_char(char *str, char c);
int			ft_issquote(char c);
int			ft_isdquote(char c);
int			ft_isbquote(char c);
void		display_ll(t_tokens *toks);

/*
** util_env.c
*/
char		*get_env_var(char **env, char *var_name);
char		**get_env(char **environ);

/*
** util_tab.c
*/
char		**init_tab(void);
size_t		get_tab_size(char **tabs);
void		print_tab(char **tabs);

/*
** execute.c
*/
void		execute_pseq(t_tokens **pseq);

#endif
