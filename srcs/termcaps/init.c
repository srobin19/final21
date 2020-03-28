#include "21sh.h"

/*
** set_termcaps_options recupere tout les pointeur de certaines fonctions des
** termcaps. Puis enregriste c'est pointeur dans la structure qu'on lui passe
** en parametre. Plus tard on pourra faire plusieur action grace à cela.
*/

static void		set_termcaps_options(t_termcaps *termcaps)
{
	termcaps->gotostr = tgetstr("cm", NULL);
	termcaps->goleft = tgetstr("le", NULL);
	termcaps->goright = tgetstr("nd", NULL);
	termcaps->godown = tgetstr("do", NULL);
	termcaps->goup = tgetstr("up", NULL);
	termcaps->gostart = tgetstr("cr", NULL);
	termcaps->clearstr = tgetstr("cl", NULL);
	termcaps->del_line = tgetstr("dl", NULL);
	termcaps->del_allline = tgetstr("cd", NULL);
	termcaps->curs_save = tgetstr("sc", NULL);
	termcaps->curs_restore = tgetstr("rc", NULL);
	termcaps->highlight_color = tgetstr("AB", NULL);
	termcaps->reset = tgetstr("me", NULL);
	termcaps->text_color = tgetstr("AF", NULL);
}

/*
** init_termcaps prend en parametre la structure termcaps
** Cette fonction recupere le contenu d'une variable d'environnement
** se trouvant dans 'TERM'. Puis va recupere l'entrée des termcaps pour
** la variable recuperer juste aprés. Ensuite grace à la function
** tcgetattr on recupere les parametre du terminal qu'on stock dans
** la structure des termcaps.
** on determine le Vmin a 1 ainsi dés qu'une lettre est taper on se met en mode
** non canonique, pareil pour le Vtime on n'attend et ainsi on se met direct
** en mode non canonique. On Détermine le mode local en mode canonique et Echo
** qui permet de ecrire les inputs.
** Une fois que nous avons changer les parametre il faut encore l'appliquer
** sur le terminal que nos changement soit pris en compte.
** Il ne reste plus qu'a remplir notre structure des termcaps et initialiser
** l'historique
*/

int			init_termcaps(t_termcaps *termcaps)
{
	char	*terminal_name;

	if ((terminal_name = getenv("TERM")) == NULL)
		exit(-1);
	if (tgetent(NULL, terminal_name) == -1)
		exit(-1);
	if (tcgetattr(0, &termcaps->term) == -1)
		exit(-1);
	termcaps->term.c_lflag &= ~(ICANON | ECHO);
	termcaps->term.c_cc[VMIN] = 1;
	termcaps->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &termcaps->term) == -1)
		exit(-1);
	set_termcaps_options(termcaps);
	if (open_history_file(termcaps) == -1)
		exit(-1);
	return (0);
}

/*
** prepare_cmd initialise for each new command, all status to have a clean line.
** After each old command
** @param {Structure t_termcaps} termcaps
** @param {integer} display_prompt Option to display the prompt
** @param {char} cmd
*/

void		prepare_cmd(t_termcaps *termcaps, int display_prompt, char **cmd)
{
	*cmd = ft_strnew(2);
  termcaps->stdin_copy = dup(0);
  termcaps->i = 0;
	termcaps->pos = 0;
	termcaps->pos_line = 0;
	termcaps->history_pos = 0;
	termcaps->cmd_len = 0;
	termcaps->edit_mode = FALSE;
	termcaps->height = 0;
	termcaps->prev_pos = 0;
	termcaps->research_mode = 0;
	if (!termcaps->stop_quote)
		termcaps->stop_quote = 0;
	termcaps->r_hist = termcaps->history_len;
	ft_bzero(termcaps->copy, NAME_MAX);
	if (tcsetattr(0, TCSADRAIN, &termcaps->term) == -1)
		exit(-1);
	termcaps->display_option = display_prompt;
	choose_display(termcaps);
}
