#include "minishell.h"

void enable_raw_mode(struct termios *orig_termios)
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

char *check_each_history(t_history *history)
{
    struct termios orig_termios;
    enable_raw_mode(&orig_termios);
    int index;
    char c;
    char command[1024];

    memset(command, 0, sizeof(command));
    index = 0;
    while (1) {
        read(STDIN_FILENO, &c, 1);
        if (c == '\n')
        {
            command[index] = '\0';
            printf("\n");
            break;
        } else if (c == '\x7f') {  // Backspace character
            if (index > 0) {
                index--;
                command[index] = '\0';
                printf("\b \b");
                fflush(stdout);
            }
        } else if (c == 27) // Escape sequence 
        {
            char seq[2];
            read(STDIN_FILENO, &seq[0], 1);
            read(STDIN_FILENO, &seq[1], 1);

            if (seq[0] == '[') {
                if (seq[1] == 'A') {  // Up arrow
                    if (history->current_history_index > 0) {
                        history->current_history_index--;
                        strcpy(command, history->commands[history->current_history_index]);
                        index = strlen(command);
                        printf("\r\033[Kminishell$ %s", command);
                        fflush(stdout);
                    }
                } else if (seq[1] == 'B') {  // Down arrow
                    if (history->current_history_index < history->count - 1) {
                        history->current_history_index++;
                        strcpy(command, history->commands[history->current_history_index]);
                        index = strlen(command);
                        printf("\r\033[Kminishell$ %s", command);
                        fflush(stdout);
                    } else if (history->current_history_index == history->count - 1) {
                        history->current_history_index++;
                        memset(command, 0, sizeof(command));
                        index = 0;
                        printf("\r\033[Kminishell$ %s", command);
                        fflush(stdout);
                    }
                }
            }
        } else {
            command[index++] = c;
            putchar(c);
            fflush(stdout);
        }
    }

    if (strlen(command) > 0) {
        add_to_history(history, command);
    }
    disable_raw_mode(&orig_termios);
    return strdup(command);
}
