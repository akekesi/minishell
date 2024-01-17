#include "../inc/minishell.h"

void    pwd_cmd()
{
    // char cwd[PATH_MAX];
    char cwd[MAX_PATH_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
        // return 1;
    }
    // return 0;
}