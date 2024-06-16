#include "minishell.h"

int my_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int my_exit() {
    return 0;
}

int my_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}

int my_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("shell");
    }
    return 1;
}

int my_export(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"export\"\n");
    } else {
        char *name = strtok(args[1], "=");
        char *value = strtok(NULL, "=");
        if (name && value) {
            setenv(name, value, 1);
        } else {
            fprintf(stderr, "invalid format for export\n");
        }
    }
    return 1;
}

int my_unset(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"unset\"\n");
    } else {
        unsetenv(args[1]);
    }
    return 1;
}

int my_env() {
    extern char **environ;
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
    return 1;
}

// int my_history(char **args, t_history *history) {
//     show_history(&history);
//     return 1;
// }

// int my_history(char **args) {
//     show_history(args);
//     return 1;
// }