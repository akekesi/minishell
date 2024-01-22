#include "../../inc/minishell.h"

int	echo_cmd(t_words *cmd)
{
	cmd = cmd->next;
	while (cmd != NULL)
	{
		printf("%s ", cmd->value);
		cmd = cmd->next;
	}
    printf("\n");
	return (1);
}
