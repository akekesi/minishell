#include "../../inc/minishell.h"

int	cd_cmd(t_words *cmd)
{
	if (chdir(cmd->next->value) != 0) {
        perror("chdir failed");
    }
    return (1);
}
