#include "../../inc/minishell.h"

void	unset_cmd(t_words *cmd)
{
	if (unsetenv(cmd->next->value) != 0)
	{
		perror("unsetenv error");
	}
}