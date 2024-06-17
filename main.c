#include "minishell.h"

void main_loop (t_llist **input_llist, t_history *history, char **envp)
{
	char	*input_str;
	char	**cmd;

	while(1)
	{
        // input_str = readline("minishell$ ");
		printf("minishell$ ");
        fflush(stdout);
		input_str = check_each_history(history);
		// printf("input_str is %s\n", input_str);

        // Process input
        // input_str = strdup(command);
		if (!input_str) {
            perror("strdup");
            break;
        }

		// pareser
		parser(input_llist, input_str);
		// printf("parser:\n");
		// llist_print(*input_llist, token_print);

		while (*input_llist)
		{
			// get command
			cmd = cmd_get(input_llist);
			// printf("get command:\n");
			// string_2d_print(cmd);

			// execute command
			// printf("execute command:\n");
			cmd_execute(cmd[0], cmd, envp, history);

			string_2d_free(cmd);
		}
		history->current_history_index = history->count;
		// free_llist(input_llist);
		free(input_str);
	}

    free_history(history);
}

int	main(int argc, char **argv, char **envp)
{
	t_llist *input_llist;

	if (argc != 1)
	{
		printf("no argument needed\n");
		return (0);
	}
	(void) argv;

	signal(SIGINT, signal_handler);

	input_llist = NULL;

	t_history history;
    init_history(&history);
	main_loop(&input_llist, &history, envp);

	return (0);
}
