#include "minishell.h"

// void main_execute(t_llist **input_llist, char **envp, char *input_str)
// void main_execute(t_llist **input_llist, char *input_str)
// {
// 	int		status;
// 	char	**cmd;

// 	parser(input_llist, input_str);
// 	// printf("parser:\n");
// 	// llist_print(*input_llist, token_print);
// 	while (*input_llist && status)
// 	{
// 		// get command
// 		// printf("%s\n", struct input_llist.data);
// 		cmd = cmd_get(input_llist);
// 		// printf("get command:\n");
// 		// string_2d_print(cmd);

// 		// execute command
// 		// printf("execute command:\n");
// 		// cmd_execute(cmd[0], cmd, envp);
// 		status = execute_with_pipes(cmd);

// 		string_2d_free(cmd);
// 		if (status == 127 || status == 0)
// 			break;
// 	}
// }

char *expand_env_vars(char *line) {
    char *result = malloc(MAX_INPUT_SIZE);
    if (!result) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    char *start = line;
    char *end = result;

    while (*start) {
        if (*start == '$') {
            start++;
            if (*start == '?') {
                int last_status = 0; // replace with your logic to get the last status
                end += sprintf(end, "%d", last_status);
                start++;
            } else {
                char var_name[100];
                int var_len = 0;
                while (start[var_len] && (isalnum(start[var_len]) || start[var_len] == '_')) {
                    var_len++;
                }
                strncpy(var_name, start, var_len);
                var_name[var_len] = '\0';
                char *value = getenv(var_name);
                if (value) {
                    end += sprintf(end, "%s", value);
                }
                start += var_len;
            }
        } else {
            *end++ = *start++;
        }
    }
    *end = '\0';

    return result;
}

char **split_line(char *line) {
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}

// void main_loop (t_llist **input_llist, t_history *history, char **envp)
void main_loop (t_history *history)
{
	// char	*input_str;
	int		status;
	char	*line;
	// char	**cmd;
    char 	**args;

	status = 1;
	while(status)
	{
        line = readline("> ");
        if (strlen(line) > 0) {
            add_history(line);  // readline history
            add_to_history(history, line);  // Custom history
        }
        char *expanded_line = expand_env_vars(line);
        args = split_line(expanded_line);
        status = execute_with_pipes(args);

        free(line);
        free(expanded_line);
        free(args);

		// printf("minishell$ ");
        // fflush(stdout);
		// input_str = check_each_history(history);
		// // printf("input_str is %s\n", input_str);

        // // Process input
        // // input_str = strdup(command);
		// if (!input_str) {
        //     perror("strdup");
        //     break;
        // }

        // args = split_line(input_str);

		// // pareser
		// if (strcmp(input_str, "history") == 0)
        //     show_history(history);
        // else
		// {
		// 	parser(input_llist, input_str);
		// 	cmd = cmd_get(input_llist);
		// 	// status = execute_with_pipes(cmd);
		// 	status = execute_with_pipes(args);
		// 	string_2d_free(cmd);
		// 	// main_execute(input_llist, envp, input_str);
		// 	// main_execute(input_llist, input_str);
		// }
		// history->current_history_index = history->count;
		// free(cmd);
		// free(input_str);
        // free(args);
	}
}

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv)
{
	t_llist *input_llist;

	if (argc != 1)
	{
		printf("no argument needed\n");
		return (0);
	}
	(void) argv;

	signal(SIGINT, signal_handler);

	input_llist = NULL;

	t_history history;
    init_history(&history);
	// main_loop(&input_llist, &history, envp);
	main_loop(&history);
    free_history(&history);
	return (0);
}
