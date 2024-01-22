#include "../../inc/minishell.h"

int	env_cmd()
{
    extern char **environ;  // Declare the external environ variable
    char **env;
    
    env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;  // Move to the next environment variable
    }
    return (0);
}
