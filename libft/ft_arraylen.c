#include "libft.h"

size_t	ft_arraylen(char	**array)
{
	char	**curr;
	size_t size;

	if (!array || !array[0])
		return (0);
	curr = array;
	size = 0;
	while (*curr)
	{
		size++;
		curr++;
	}
	return (size);
}
