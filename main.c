#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		length;
	char	**cmd;
	char	*input_str;
	t_llist *input_llist;
	t_llist *cmd_llist;
	t_llist *cmd_node;

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

		cmd_llist = NULL;
		while (input_llist)
		{
			// get command
			cmd = cmd_get(&input_llist);
			printf("get command:\n");
			string_2d_print(cmd);

			cmd_node = llist_create(cmd);
			llist_add(&cmd_llist, cmd_node);
		}
		length = llist_len(cmd_llist);
		printf("cmd_llist (%d):\n", length);
		
		llist_print(cmd_llist, string_2d_print);
		// cmd_node = cmd_llist->prev;
		// while (length)
		// {
		// 	// execute command
		// 	cmd_node = cmd_node->next;
		// 	cmd = cmd_node->data;
		// 	printf("execute command:\n");
		// 	cmd_execute(cmd[0], cmd, envp);
		// 	length -= 1;
		// }
		cmd_node = cmd_llist;
		// first pipe/child ???
		while (1)
		{
			// execute command
			cmd = cmd_node->data;
			printf("execute command:\n");
			cmd_execute(cmd[0], cmd, envp);
			cmd_node = cmd_node->next;
			if (cmd_node == cmd_llist)
				break ;
		}
		// last pipe/child ???
		free(input_str);
		llist_free(&cmd_llist, string_2d_free);
	}
}
