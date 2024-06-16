#include "minishell.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "echo",
    "pwd",
    "export",
    "unset",
    "env",
    // "history"
};

int (*builtin_func[])(char **) = {
    &my_cd,
    &my_help,
    &my_exit,
    &my_echo,
    &my_pwd,
    &my_export,
    &my_unset,
    &my_env,
    // &my_history
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch(args);
}

int execute_with_pipes(char **args) {
    int pipefd[2];
    pid_t pid1, pid2;
    char **cmd1 = args;
    char **cmd2 = NULL;

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL;
            cmd2 = &args[i + 1];
            break;
        }
    }

    if (cmd2 == NULL) {
        return execute(args);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid1 = fork();
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (execvp(cmd1[0], cmd1) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid1 < 0) {
        perror("fork");
        return 1;
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        if (execvp(cmd2[0], cmd2) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid2 < 0) {
        perror("fork");
        return 1;
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 1;
}

int launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0) {
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    return 1;
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
            } else if (strcmp(args[i], ">>") == 0) {
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) {
                    perror("open");
                    return 1;
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
            } else if (strcmp(args[i], "<") == 0) {
                int fd = open(args[i + 1], O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    return 1;
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[i] = NULL;
            }
        }

        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int my_help() {
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}