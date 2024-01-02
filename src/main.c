#include "../inc/minishell.h"

void	prompt()
{
	printf("minishell> ");
}

char*	read_input()
{
	char* buffer = malloc(MAX_INPUT_SIZE);
	if (!buffer)
	{
		printf("malloc error");
		exit(EXIT_FAILURE);
	}

	if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	// Remove newline character
	buffer[strcspn(buffer, "\n")] = '\0';

	return buffer;
}

t_words *parse_input(char* input) {
    t_words *head = NULL, *current = NULL;
    char buffer[MAX_ARG_SIZE];
    int i = 0, k = 0;

    while (input[i]) {
        if (input[i] != ' ') {
            buffer[k] = input[i];
            k++;
        } else {
            if (k > 0) {
                buffer[k] = '\0';

                t_words *new_node = (t_words *)malloc(sizeof(t_words));
                new_node->value = strdup(buffer);
                new_node->next = NULL;
                new_node->prev = current;

                if (current) {
                    current->next = new_node;
                } else {
                    head = new_node; // Set the first node as head
                }

                current = new_node;
                k = 0;
            }
        }
        i++;
    }

    // Handle the last word
    if (k > 0) {
        buffer[k] = '\0';
        t_words *new_node = (t_words *)malloc(sizeof(t_words));
        new_node->value = strdup(buffer);
        new_node->next = NULL;
        new_node->prev = current;

        if (current) {
            current->next = new_node;
        } else {
            head = new_node; // In case input is a single word
        }
    }

    return head;
}

// char**	parse_input(char* input)
// {
// 	char** args;
// 	int i;
// 	int j;
// 	int k;
	
// 	args = (char **)malloc(MAX_ARG_SIZE * sizeof(char*));
// 	if (!args) {
// 		printf("malloc error");
// 		exit(EXIT_FAILURE);
// 	}
// 	for (i = 0; i < MAX_ARG_SIZE; i++) {
//         args[i] = (char *)malloc(MAX_ARG_SIZE * sizeof(char)); // Allocate memory for each argument
//         if (!args[i]) {
//             printf("malloc error\n");
//             exit(EXIT_FAILURE);
//         }
//     }
	
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (input[i])
// 	{
// 		if (input[i] != ' ')
// 		{
// 			args[j][k] = input[i];
// 			k++;
// 		}
// 		else if (input[i] == ' ' && input[i + 1] != ' ')
// 		{
// 			args[j][k] = '\0';
// 			j++;
// 			k = 0;
// 		}
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return args;
// }

void	execute_command(char **cmd)
{
	pid_t pid = fork();

    if (pid == 0) {  // Child process
		execvp(cmd[0], cmd);
		perror("execvp");
		exit(EXIT_FAILURE);
	} else if (pid > 0) {  // Parent process
		waitpid(pid, NULL, 0);
	} else {
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		prompt();
		fflush(stdout);
	}
}

/**
 * signal(SIGINT, signal_handler); -> Handle Ctrl-C
 * signal(SIGQUIT, SIG_IGN);       -> Ignore Ctrl-\
*/
int	main(int ac, char **av, char **envp)
{
	char	*input;
	// char	**cmd;
	t_words	*cmd;

	// envp ??
    // for (int i = 0; envp[i] != NULL; i++) {
    //     printf("%s\n", envp[i]);
    // }

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		prompt();
		input = read_input();
		cmd = parse_input(input);
		// printf("%s\n", cmd->value);
		// printf("%s\n", cmd->prev->value);
		printf("%s\n", cmd[2].value);
		printf("%s\n", cmd[2].next->value);
		printf("%s\n", cmd[2].prev->value);
		// Example: Execute the command
		// printf("You typed: %s\n", *cmd);
		// execute_command(cmd);
		// free(input);
		// free(cmd);
	}

	return (0);
}
