#include "../inc/minishell.h"

void	execute_command(char *cmd);
void	setup_signal_handlers();
void	initialize_minishell();

int	main()
{
	char	*input;

	// Initial setup for minishell
	initialize_minishell();

	// Main loop
	while (42)
	{
		input = readline("minishell> "); // Prompt
		if (!input)
			break; // Exit on Ctrl-D
		add_history(input); // Add input to history
		execute_command(input); // Execute the command
		free(input); // Free the allocated input
	}
	printf("\nOkay bye:)\n");
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
	if (cmd == NULL)
		return;

	// Here you'll parse and execute the command
	// For now, let's just print the command
	printf("You typed: %s\n", cmd);

	// Future: Add parsing, finding the right executable, and executing it
}
