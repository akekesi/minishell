#include "../../inc/minishell.h"

int	exit_cmd(t_words *cmd)
{
    // printf("Exiting with status code %s\n", cmd->next->value);
    // exit(atoi(cmd->next->value));
    exit(0);
    return (0);
}
