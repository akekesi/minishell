#include "minishell.h"

char	**string_2d_init(int n)
{
	int		i;
	char	**str;

	str = (char **)malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n + 1)
	{
		str[i] = NULL;
		i++;
	}
	return (str);
}

void	string_2d_free(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n + 1)
	{
		free(str[n]);
		i++;
	}
	free(str);
}