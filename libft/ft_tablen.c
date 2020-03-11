#include "libft.h"

size_t	ft_tablen(char	**tab)
{
	char	**curr;
	size_t size;

	if (!tab || !tab[0])
		return (0);
	curr = tab;
	size = 0;
	while (*curr)
	{
		size++;
		curr++;
	}
	return (size);
}
