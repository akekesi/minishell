#include "minishell.h"

int	cmd_len(t_llist **head)
{
	int		n;
	int		flag;
	t_llist	*tmp;
	t_token	*token;

	n = 0;
	if (!*head)
		return (n);
	flag = 0;
	tmp = *head;
	while (1)
	{
		token = tmp->data;
		if (!strcmp(token->type, "pipe"))
			flag = -1;
		else if (!strcmp(token->type, "space"))
		{
			if (flag)
				flag = 0;
		}
		else
		{
			if (!flag)
			{
				n++;
				flag = 1;
			}	
		}
		tmp = tmp->next;
		if (flag == -1 || tmp == *head)
			break;
	}
	return (n);
}

t_command *cmd_get(t_llist **head)
{
    int i;
    int n;
    int flag;
    char *str;
    char *str_tmp;
    t_command *cmd;
    t_llist *tmp;
    t_llist *node;
    t_token *token;

    n = cmd_len(head);
    cmd = malloc(sizeof(t_command));
    cmd->args = string_2d_init(n);
    cmd->in_fd = STDIN_FILENO;  // Default input is stdin
    cmd->out_fd = STDOUT_FILENO; // Default output is stdout
    if (!*head)
        return NULL;
    i = 0;
    flag = 0;
    str = NULL;
    tmp = *head;
    while (tmp)
    {
        token = tmp->data;
        if (!strcmp(token->type, "pipe"))
        {
            flag = -1;
            cmd->out_fd = -1; // Will be set up in main_loop
        }
        else if (!strcmp(token->type, "space"))
        {
            if (str)
            {
                cmd->args[i] = str;
                i++;
                str = NULL;
            }
        }
        else
        {
            str_tmp = str;
            str = ft_strcat(str_tmp, token->string);
            free(str_tmp);
        }
        tmp = tmp->next;
        node = llist_del(&tmp);
        llist_free(&node, token_free);
        if (flag == -1)
            break;
    }
    if (str)
        cmd->args[i] = str;
    *head = tmp;
    return cmd;
}

char	*cmd_access(t_llist *paths, char *cmd)
{
	char	*full_path;
	t_llist	*tmp;

	if (!paths)
		return (NULL);
	tmp = paths;
	while (1)
	{
		full_path = ft_strcat(tmp->data, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		tmp = tmp->next;
		if (paths == tmp)
			return (NULL);
	}
}

void cmd_execute(t_command *cmd, char **envp, t_history *history)
{
    int i;
    char *cmd_;
    char *path;
    t_llist *paths;

    if (!strcmp(cmd->args[0], "cd"))
        return cd_cmd(cmd->args);
    else if (!strcmp(cmd->args[0], "echo"))
        return echo_cmd(cmd->args);
    else if (!strcmp(cmd->args[0], "env"))
        return env_cmd();
    else if (!strcmp(cmd->args[0], "exit"))
        return exit_cmd(cmd->args);
    else if (!strcmp(cmd->args[0], "export"))
        return export_cmd(cmd->args);
    else if (!strcmp(cmd->args[0], "pwd"))
        return pwd_cmd();
    else if (!strcmp(cmd->args[0], "unset"))
        return unset_cmd(cmd->args);
    else if (!strcmp(cmd->args[0], "history"))
        return show_history(history);

    i = 0;
    while (1)
    {
        if (!strncmp(envp[i], "PATH=", 5))
            break;
        if (envp[i] == NULL)
            break;
        i++;
    }

    paths = ft_strsplit(&(envp[i])[5], ':');
    cmd_ = ft_strcat("/", cmd->args[0]);
    path = cmd_access(paths, cmd_);
    free(cmd_);
    llist_free(&paths, ft_strfree);

    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (cmd->in_fd != STDIN_FILENO)
        {
            dup2(cmd->in_fd, STDIN_FILENO);
            close(cmd->in_fd);
        }
        if (cmd->out_fd != STDOUT_FILENO)
        {
            dup2(cmd->out_fd, STDOUT_FILENO);
            close(cmd->out_fd);
        }
        execve(path, cmd->args, envp);
        perror(cmd->args[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (cmd->in_fd != STDIN_FILENO)
            close(cmd->in_fd);
        if (cmd->out_fd != STDOUT_FILENO)
            close(cmd->out_fd);
        waitpid(pid, NULL, 0);
    }
    free(path);
}
