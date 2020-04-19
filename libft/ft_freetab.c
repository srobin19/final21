#include "libft.h"

void	ft_freetab(char **table)
{
	char	**curr;

	if (!table)
		return ;
	curr = table;
	while (*curr)
	{
		free(*curr);
		curr++;
	}
	free(table);
}
