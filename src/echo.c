#include "../inc/minishell.h"

void	echo_cmd(t_words *cmd)
{
	cmd = cmd->next;
	while (cmd != NULL)
	{
		printf("%s ", cmd->value);
		cmd = cmd->next;
	}
    printf("\n");
}
