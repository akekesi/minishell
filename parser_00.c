#include "minishell.h"

t_llist	*parser(char *str)
{
	int		i;
	int		j;
	char	*text;
	char	*type;
	t_token	*token;
	t_llist	*node;
	t_llist	*input;

	if (!str)
		return (NULL);
	i = 0;
	input = NULL;
	while (str[i])
	{
		// if space
		if (ft_isspace(str[i]))
		{
			while (ft_isspace(str[i])) // skip spaces
			{
				i++;
			}
			type = "space";
			text = ft_strget("space", 0, 5);
			token = token_create(text, type);
			node = llist_create(token);
			llist_add(&input, node);
		}
		else
		{
			// if "
			if (str[i] == '\"')
			{
				i++;
				j = ft_strlen_to_char(&str[i], '\"');
				type = "text";
				if (j < 0) // no closing "
				{
					printf("-->no closing \" <--\n");
					j *= -1;
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j + 1;
			}
			// if '
			else if (str[i] == '\'')
			{
				i++;
				j = ft_strlen_to_char(&str[i], '\'');
				type = "text";
				if (j < 0) // no closing '
				{
					printf("-->no closing \' <--\n");
					j *= -1;
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j + 1;
			}
			// if > or >>
			else if (str[i] == '>')
			{
				j = 1;
				type = "redir_to_w";
				if (str[i+1] == '>')
				{
					j = 2;
					type = "redir_to_a";
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j;
			}
			// if < or <<
			else if (str[i] == '<')
			{
				j = 1;
				type = "redir_from_r";
				if (str[i+1] == '<')
				{
					j = 2;
					type = "redir_from_d";
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j;
			}
			// if | or ||
			else if (str[i] == '|')
			{
				j = 1;
				type = "pipe";
				if (str[i+1] == '|')
				{
					j = 2;
					type = "or";
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j;
			}
			// if & or &&
			else if (str[i] == '&')
			{
				j = 1;
				type = "background";
				if (str[i+1] == '&')
				{
					j = 2;
					type = "and";
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j;
			}
			else
			{
				j = ft_strlen_to_next(&str[i]);
				type = "text";
				if (j < 0)
				{
					j *= -1;
				}
				text = ft_strget(str, i, i+j);
				token = token_create(text, type);
				node = llist_create(token);
				llist_add(&input, node);
				i += j;
			}
		}
	}
	llist_print(input, token_print);
	llist_free(&input, token_free);
	return (NULL);
}
