#include "../../inc/minishell.h"

int	unset_cmd(t_words *cmd)
{
	if (unsetenv(cmd->next->value) != 0)
	{
		perror("unsetenv error");
	}
	return (1);
}