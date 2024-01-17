#include "../inc/minishell.h"

extern char **environ;  // Declare the external environ variable

void	env_cmd()
{
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;  // Move to the next environment variable
    }
}
