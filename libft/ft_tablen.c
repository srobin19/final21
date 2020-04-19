int ft_tablen(char **tab)
{
	int	len;
	char	**roam;

	if (!tab || !(*tab))
		return (0);
	len = 0;
	roam = tab;
	while (*roam)
	{
		len++;
		roam++;
	}
	return (len);
}
