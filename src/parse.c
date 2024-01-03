#include "../inc/minishell.h"

t_words *parse_input(char* input)
{
	t_words	*head;
	t_words	*current;
	t_words	*new_node;
	char buffer[MAX_ARG_SIZE];
	int i;
	int	j;

	head = NULL;
	current = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != ' ')
		{
			buffer[j] = input[i];
			j++;
		}
		else if (j > 0)
		{
			buffer[j] = '\0';	
			new_node = (t_words *)malloc(sizeof(t_words));
			new_node->value = strdup(buffer);
            new_node->prev = current;
            new_node->next = NULL;
			if (current)
			{
				current->next = new_node;
				// new_node->prev = current;
			}
			else
			{
				head = new_node;
				// new_node->prev = new_node;
			}
			current = new_node;
			j = 0;
		}
		i++;
	}
	// head->prev = current;
	// Handle the last word
	if (j > 0)
	{
		buffer[j] = '\0';
		new_node = (t_words *)malloc(sizeof(t_words));
		new_node->value = strdup(buffer);
        new_node->prev = current;
        // new_node->next = head;
        new_node->next = NULL;
		// if (j == i)
		// {
		// 	new_node->next = new_node;
		// 	new_node->prev = new_node;
		// }
		if (current)
			current->next = new_node;
		else
			head = new_node; // In case input is a single word
		// printf("hi");

		// printf("%s\n", head->value);
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
