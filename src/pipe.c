#include "../inc/minishell.h"

// Function to handle pipe execution
void	pipe_cmd(t_words *cmd)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {  // Child process
		close(pipefd[0]); // Close unused read end
		dup2(pipefd[1], STDOUT_FILENO);  // Connect stdout to pipe write end
		close(pipefd[1]);

		execute_command(cmd);  // Execute the first part of the pipe

		exit(EXIT_SUCCESS);
	} else {  // Parent process
		close(pipefd[1]); // Close unused write end
		dup2(pipefd[0], STDIN_FILENO);  // Connect stdin to pipe read end
		close(pipefd[0]);

		wait(NULL);  // Wait for child process to finish

		// Execute the next part of the pipe
		if (cmd->next != NULL) {
			execute_command(cmd->next);
		}
	}
}
