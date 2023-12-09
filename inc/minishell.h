#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>     // printf, scanf
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // strcpy, strcat, strtok
# include <unistd.h>    // POSIX operatubg system API
# include <sys/types.h> // pid_t
# include <sys/wait.h>  // waitpid
# include <signal.h>    // SIGINT
# include <fcntl.h>     // O_RDONLY, O_WRONLY

# define MAX_INPUT_SIZE 1024
# define MAX_ARG_SIZE 64
# define MAX_PATH_SIZE 256

void signal_handler(int signo);

#endif
