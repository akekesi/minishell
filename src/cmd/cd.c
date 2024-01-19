#include "../../inc/minishell.h"

void	cd_cmd(t_words *cmd)
{
	if (chdir(cmd->next->value) != 0) {
        perror("chdir failed");
    }
}
