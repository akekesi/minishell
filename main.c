#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1)
	{
		printf("no argument needed\n");
		return (0);
	}
	(void) argv;
	(void) envp;

	signal(SIGINT, signal_handler);

	while(1)
	{
		input = readline("minishell$ ");
		if (!input)
			exit(1);
		printf("input-main: -->%s<--\n", input);
		parser(input);
		free(input);
	}
}
