/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q21sh.h                                             :+:      :+:    :+:   */
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

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "21sh.h"

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

typedef struct	s_pwd
{
	char	*current_wd;
	char	*old_wd;
}		t_pwd;

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
t_tokens	*lexer(char *input, char **env);
int		expand(char **curr_c, char **env, char **input);
/*
** tokens_get.c
*/
int			is_blank_char(char c);
int			is_operator(char *c);
int			is_part_operator(char *curr_c, int op);
char			*ctos(char c);
void			add_char_to_token(t_tokens *tok, char c);
char			*add_char_to_string(char *str, char c);

/*
**
*/
char		**set_env(char **cmd, char ***env);
int		replace_env(char **cmd, char **env);
int		env_match(char *to_find, char *curr_var);
char		*set_var(char *to_set, char *name, char *value);

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
int			is_expandable(char *curr_c, char *input);

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
** util_array.c
*/
char		**init_array(void);
size_t		get_array_size(char **array);
void		print_array(char **array);

/*
** util_array.c
*/
void		update_s_pwd(t_pwd *pwd);
int		update_pwd(char ***env, char *var, char *value);
int		init_pwd(t_pwd *pwd);
void		free_pwd(t_pwd *pwd);

/*
** execute.c
*/
void		execute_pseq(t_tokens **pseq, t_pwd *pwd, char ***env);

/*
** execute.c
*/
void		cd(char **cmd, char ***env, t_pwd *pwd);
int			prompt_loop(char ***env, t_pwd *pwd);

#endif
