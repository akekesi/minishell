#include "../inc/minishell.h"

t_words *parse_input(char* input)
{
	t_words	*head;
	t_words	*current;
	t_words	*new_node;
	char buffer[MAX_ARG_SIZE];
	int i;
	int	j;
	int	quote_flag;

	head = NULL;
	current = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	i = 0;
	j = 0;
	quote_flag = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (quote_flag == 1)
				quote_flag = 0;
			else
				quote_flag = 1;
		}
		else if (input[i] != ' ' || quote_flag == 1)
		{
			buffer[j] = input[i];
			j++;
		}
		else if (j > 0 && quote_flag == 0)
		{
			buffer[j] = '\0';	
			new_node = (t_words *)malloc(sizeof(t_words));
			new_node->value = strdup(buffer);
            new_node->prev = current;
            new_node->next = NULL;
			if (current)
				current->next = new_node;
			else
				head = new_node;
			current = new_node;
			j = 0;
		}
		i++;
	}
	// Handle the last word
	if (j > 0)
	{
		buffer[j] = '\0';
		new_node = (t_words *)malloc(sizeof(t_words));
		new_node->value = strdup(buffer);
        new_node->prev = current;
        new_node->next = NULL;
		if (current)
			current->next = new_node;
		else
			head = new_node; // In case input is a single word
	}
	return head;
}

// void    pipe(char *s)
// {
//     int i;

    // while (*s)
    // {
    //     if (s == )
    //     s++;
    //     i++;
    // }
// }
