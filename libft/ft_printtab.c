void ft_printab(char **tab)
{
	char	**curr;

	if (!tab || !(*tab))
		return ;
	printf("tab content: \n");
	curr = tab;
	while (*curr)
	{
		printf("> %s\n", *curr);
		curr++;
	}
	return ;
}
