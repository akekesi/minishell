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
		if (cmd)
		{
			printf("%s\n", cmd->value);
			cmd++;
			printf("%s\n", cmd[1].value);
			cmd++;
			printf("%s\n", cmd[2].value);
		}
		// printf("%s\n", cmd[1].next->value);
		// printf("%s\n", cmd[1].prev->value);
		// Example: Execute the command
		// printf("You typed: %s\n", *cmd);
		// execute_command(cmd);
		// free(input);
		// free(cmd);
	}

	return (0);
}
