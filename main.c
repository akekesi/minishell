#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	char	*input_str;
	t_llist *input_llist;

	if (argc != 1)
	{
		printf("no argument needed\n");
		return (0);
	}
	(void) argv;

	signal(SIGINT, signal_handler);

	input_llist = NULL;
	while(1)
	{
		// read line
		input_str = readline("minishell$ ");
		if (!input_str)
			exit(1);
		printf("read line:\n%s\n", input_str);

		// pareser
		parser(&input_llist, input_str);
		printf("parser:\n");
		llist_print(input_llist, token_print);

		while (input_llist)
		{
			// get command
			cmd = cmd_get(&input_llist);
			printf("get command:\n");
			string_2d_print(cmd);

			// execute command
			printf("execute command:\n");
			cmd_execute(cmd[0], cmd, envp);

			string_2d_free(cmd);
		}
		free(input_str);
	}
}
