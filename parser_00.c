#include "minishell.h"

t_llist	*parser(char *str)
{
	int		i;
	t_llist	*input_llist;

	if (!str)
		return (NULL);
	i = 0;
	input_llist = NULL;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i = parser_space(&input_llist, str, i);
		else if (str[i] == '\'')
			i = parser_quote_s(&input_llist, str, i);
		else if (str[i] == '\"')
			i = parser_quote_d(&input_llist, str, i);
		else if (str[i] == '>')
			i = parser_redir_t(&input_llist, str, i);
		else if (str[i] == '<')
			i = parser_redir_f(&input_llist, str, i);
		else if (str[i] == '|')
			i = parser_bar(&input_llist, str, i);
		else if (str[i] == '&')
			i = parser_and(&input_llist, str, i);
		else
			i = parser_string(&input_llist, str, i);
	}
	llist_print(input_llist, token_print);
	while (input_llist)
	{
		printf("n: %d\n", get_cmd_len(&input_llist));
		get_cmd(&input_llist);
	}
	llist_print(input_llist, token_print);
	llist_free(&input_llist, token_free);

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
	int		i;
	int		n;
	int		flag;
	char	*str;
	char	*str_tmp;
	char	**cmd;
	t_llist	*tmp;
	t_llist	*node;
	t_token	*token;

	n = get_cmd_len(head);
	cmd = string_2d_init(n);
	printf("cmd:\n");
	if (!*head)
		return (NULL);
	i = 0;
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
				cmd[i] = str; // hogy kell atadni???
				printf("%s\n", cmd[i]);
				i++;
				free(str);
				str = NULL;
			}
		}
		else
		{
			// concatenate str
			str_tmp = str; // hogy kell atadni???
			str = ft_strcat(str_tmp, token->string);
			free(str_tmp);
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
		cmd[i] = str; // hogy kell atadni???
		printf("%s\n", cmd[i]);
		free(str);
	}
	*head = tmp;
	string_2d_free(cmd, n); // only for testing
	return (NULL);
}
