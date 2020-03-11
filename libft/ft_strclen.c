
#include "libft.h"

size_t	ft_strclen(const char *str, char c)
{
	size_t count;

	count = 0;
	while (str[count] && str[count] != c)
		count++;
	return (count);
}
