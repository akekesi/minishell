#ifndef MINISHELL_H
# define MINISHELL_H
// # include <stdio.h>     // printf, scanf
// # include <stdlib.h>    // malloc, free, exit
// # include <string.h>    // strcpy, strcat, strtok
// # include <unistd.h>    // POSIX operatubg system API
// # include <sys/types.h> // pid_t
// # include <sys/wait.h>  // waitpid
// # include <signal.h>    // SIGINT
// # include <fcntl.h>     // O_RDONLY, O_WRONLY
#include <stdio.h> // printf, scanf, fgets, fputs, fopen, fclose, fprintf, fscanf
#include <stdlib.h> // malloc, free, exit, atoi, qsort, abs
#include <unistd.h> // fork, pipe, read, write, close, chdir, getcwd, sleep, [new]chdir, [new]getcwd
#include <string.h> // strlen, strcpy, strcat, strcmp, strncpy, strerror, memset
#include <readline/readline.h> // readline (read a line of input from the user).
#include <readline/history.h> // add_history (add a line to the history), using_history (start using the history)
#include <signal.h>

# define MAX_INPUT_SIZE 1024
# define MAX_ARG_SIZE 64
# define MAX_PATH_SIZE 256

void sigint_handler(int sig);
void setup_signal_handlers();

#endif
