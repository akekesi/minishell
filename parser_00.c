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
		// if "
		else if (str[i] == '\"')
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
	llist_print(input, token_print);
	while (input)
	{
		printf("n: %d\n", get_cmd_len(&input));
		get_cmd(&input);
	}
	llist_print(input, token_print);
	llist_free(&input, token_free);
	return (NULL);
}

int	get_cmd_len(t_llist **head)
{
	int		n;
	int		flag;
	t_llist	*tmp;
	t_token	*token;

	n = 0;
	if (!*head)
		return (n);
	flag = 0;
	tmp = *head;
	while (1)
	{
		token = tmp->data;
		if (!strcmp(token->type, "pipe"))
			flag = -1;
		else if (!strcmp(token->type, "space"))
		{
			if (flag)
				flag = 0;
		}
		else
		{
			if (!flag)
			{
				n++;
				flag = 1;
			}
				
		}
		tmp = tmp->next;
		if (flag == -1 || tmp == *head)
			break;
	}
	return (n);
}

char **get_cmd(t_llist **head)
{
	int		flag;
	char	*str;
	t_llist	*tmp;
	t_llist	*node;
	t_token	*token;

	printf("cmd:\n");
	if (!*head)
		return (NULL);
	flag = 0;
	str = NULL;
	tmp = *head;
	while (tmp)
	{
		token = tmp->data;
		if (!strcmp(token->type, "pipe"))
			flag = -1;
		else if (!strcmp(token->type, "space"))
		{
			if (str)
			{
				// add str to char ** if str != empty
				printf("\n");
				str = NULL;
			}
		}
		else
		{
			// concatenate str
			str = token->text;
			printf("%s", str);
		}
		tmp = tmp->next;
		node = llist_del(&tmp);
		llist_free(&node, token_free);
		if (flag == -1)
			break;
	}
	if (str)
	{
		// add str to char ** if str != empty
		printf("\n");
	}
	*head = tmp;
	return (NULL);
}
