#include "minishell.h"

char *expand_home_directory(char *path) {
    if (path[0] == '~') {
        char *home_dir = getenv("HOME");
        if (!home_dir) {
            struct passwd *pw = getpwuid(getuid());
            home_dir = pw->pw_dir;
        }
        if (!home_dir) {
            fprintf(stderr, "Error: HOME environment variable is not set.\n");
            return NULL;
        }
        // Allocate space for the new path
        char *expanded_path = malloc(strlen(home_dir) + strlen(path));
        if (!expanded_path) {
            perror("malloc");
            return NULL;
        }
        // Copy the home directory and the rest of the path
        strcpy(expanded_path, home_dir);
        strcat(expanded_path, path + 1);  // Skip the '~' character
        return expanded_path;
    }
    // If path doesn't start with '~', return a copy of the original path
    return strdup(path);
}

void	cd_cmd(char **args)
{
    char *path = args[1];
    if (!path || strcmp(path, "~") == 0) {
        path = "~";
    }
    char *expanded_path = expand_home_directory(path);
    if (!expanded_path) {
        return ;
    }
    if (chdir(expanded_path) != 0) {
        perror("chdir failed");
        free(expanded_path);
        return ;
    }
    free(expanded_path);
}

void	echo_cmd(char **args)
{
    int i;
    int n_flag;
    
    i = 1;
    n_flag = 0;
	while (args[i] != NULL)
	{
        if (strcmp(args[i], "-n") == 0)
        {
            i++;
            n_flag = 1;
            continue;
        }
        if (n_flag)
        {
            printf("%s", args[i]);
            break;
        }
        else
        {
            printf("%s \n", args[i]);
            break;
        }
	}
}

void	env_cmd()
{
    extern char **environ;  // Declare the external environ variable
    char **env;
    
    env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;  // Move to the next environment variable
    }
}

void	exit_cmd(char **args)
{
    int exit_code;
    
    exit_code = 0;
    if (args[1] != NULL)
        exit_code = atoi(args[1]);
    exit(exit_code);
    // printf("Exiting with status code %s\n", cmd->next->value);
    // exit(atoi(cmd->next->value));
}

void	export_cmd(char **args)
{
	// Assuming the format is "export VAR=value"
	char* variable = strtok(args[1], "=");
	char* value = strtok(NULL, "");

	if (variable == NULL || value == NULL) {
		fprintf(stderr, "Invalid format. Use 'export VAR=value'.\n");
	}

	// Skip the "export " part to get the actual variable name
	// variable += 7;

	if (setenv(variable, value, 1) != 0) {
		perror("setenv failed");
	}
}

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
}

void	unset_cmd(char **args)
{
	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv error");
	}
}
