/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:53:51 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/05 18:33:43 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char**	parse_input(char* input)
{
	char** args;
	
	args = (char **)malloc(MAX_ARG_SIZE * sizeof(char*));
	if (!args) {
		printf("malloc error");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	char* token = strtok(input, " ");
	while (token != NULL) {
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}

void	execute_command(char** args)
{
	pid_t pid = fork();

    if (pid == 0) {  // Child process
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	} else if (pid > 0) {  // Parent process
		waitpid(pid, NULL, 0);
	} else {
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

/**
 * signal(SIGINT, signal_handler); -> Handle Ctrl-C
 * signal(SIGQUIT, SIG_IGN);       -> Ignore Ctrl-\
*/
int	main(void)
{
	char	*input;
	char	**args;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		prompt();
		input = read_input();
		args = parse_input(input);
		// Example: Execute the command
		execute_command(args);
		free(input);
		free(args);
	}

	return (0);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		prompt();
		fflush(stdout);
	}
}
