#include "21sh.h"

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
