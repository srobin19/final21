#include "21sh.h"


// - create init_pwd (to keep track of the current working directory)
// - get current environment and copy it
// - display the welcome text of the shell
// - launch te prompt loop (see sh21.c)
int			main(void)
{
	extern char	**environ;
	char		**env;
	t_pwd		pwd;

	if (!init_pwd(&pwd))
		exit(EXIT_FAILURE);
	if (!(env = get_env(environ)))
		return (-1);
	title();
	prompt_loop(&env, &pwd);
	return (0);
}
