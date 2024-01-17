#include "../inc/minishell.h"

void	export_cmd(t_words *cmd)
{
	// Assuming the format is "export VAR=value"
	char* variable = strtok(cmd->next->value, "=");
	char* value = strtok(NULL, "");

	if (variable == NULL || value == NULL) {
		fprintf(stderr, "Invalid format. Use 'export VAR=value'.\n");
		return;
	}

	// Skip the "export " part to get the actual variable name
	// variable += 7;

	if (setenv(variable, value, 1) != 0) {
		perror("setenv failed");
	}
}

// int main() {
//     // Example usage
//     handleExport("export PATH=/usr/bin");

//     // Print the new PATH to verify that it worked
//     printf("PATH: %s\n", getenv("PATH"));

//     return 0;
// }