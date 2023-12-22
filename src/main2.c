/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njn0te <njn0te@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:15:20 by tnakajo           #+#    #+#             */
/*   Updated: 2023/12/23 03:52:04 by njn0te           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Function prototypes
void	execute_command(char *cmd);
void	setup_signal_handlers();
void	initialize_minishell();

int main()
{
	char	*input;

	// Initial setup for minishell
	initialize_minishell();

	// Main loop
	while (42) {
		input = readline("minishell> "); // Prompt
		if (!input) {
			break; // Exit on Ctrl-D
		}

		// Add input to history
		add_history(input);

		// Execute the command
		execute_command(input);

		// Free the allocated input
		free(input);
	}

	return 0;
}

void	initialize_minishell()
{
	// Setup signal handlers, environment, etc.
	setup_signal_handlers();
	// Other initialization code...
}

void setup_signal_handlers()
{
	// Implement signal handling (e.g., for Ctrl-C)
}

void execute_command(char *cmd) {
	if (cmd == NULL) {
		return;
	}

	// Here you'll parse and execute the command
	// For now, let's just print the command
	printf("Executing command: %s\n", cmd);

	// Future: Add parsing, finding the right executable, and executing it
}
