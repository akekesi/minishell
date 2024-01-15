#include "../inc/minishell.h"

void	prompt()
{
	printf("minishell> ");
}

char	*read_input()
{
	char	*buffer = malloc(MAX_INPUT_SIZE);
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
	t_words	*cmd;
	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		prompt();
		input = read_input();
		cmd = parse_input(input);
		while (cmd != NULL)
		{
			printf("-->%s\n", cmd->value);
			cmd = cmd->next;
		}
		// execute_command(cmd);
		// free(input);
		// free(cmd);
	}

	return (0);
}