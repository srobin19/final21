
#include "libft.h"

char		*copy_s2(char **s2, int i)
{
	char	*new;

	if (!(new = ft_strdup(*s2)))
		return (NULL);
	if (i == 1 || i == 2)
		ft_strdel(s2);
	return (new);
}

char		*copy_s1(char **s1, int i)
{
	char	*new;

	if (!(new = ft_strdup(*s1)))
		return (NULL);
	if (i == 0 || i == 2)
		ft_strdel(s1);
	return (new);
}

void		delete_both(int i, char **s1, char **s2)
{
	if (i == 2)
	{
		ft_strdel(s1);
		ft_strdel(s2);
	}
}

char		*ft_strjoin_free(char **s1, char **s2, int i)
{
	char	*new;
	int		k;
	int		l;

	if (*s1 == NULL && *s2 != NULL)
		return (copy_s2(s2, i));
	if (*s2 == NULL && *s1 != NULL)
		return (copy_s1(s1, i));
	if (*s1 == NULL && *s2 == NULL)
		return (ft_strnew(0));
	if (!(new = ft_strnew((ft_strlen(*s1) + ft_strlen(*s2)))))
		return (NULL);
	k = -1;
	while ((*s1)[++k])
		new[k] = (*s1)[k];
	l = 0;
	while ((*s2)[l])
		new[k++] = (*s2)[l++];
	if (i == 0)
		ft_strdel(s1);
	if (i == 1)
		ft_strdel(s2);
	delete_both(i, s1, s2);
	return (new);
}
