#include "../inc/minishell.h"

t_words *parse_input(char* input)
{
	t_words	*head;
	t_words	*current;
	t_words	*new_node;
	char buffer[MAX_ARG_SIZE];
	int i;
	int	j;
    int single_quote_flag = 0;
	int	double_quote_flag = 0;

	head = NULL;
	current = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	i = 0;
	j = 0;
	single_quote_flag = 0;
	while (input[i])
	{
		if (input[i] == '\'' && double_quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		else if (input[i] == '\"' && single_quote_flag == 0)
			double_quote_flag = !double_quote_flag;
		else if (input[i] != ' ' || single_quote_flag || double_quote_flag)
			buffer[j++] = input[i];
		else if (j > 0 && !single_quote_flag && !double_quote_flag)
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
