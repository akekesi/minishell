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

char **cmd_get(t_llist **head)
{
	int		i;
	int		n;
	int		flag;
	char	*str;
	char	*str_tmp;
	char	**cmd;
	t_llist	*tmp;
	t_llist	*node;
	t_token	*token;

	n = cmd_len(head);
	cmd = string_2d_init(n);
	if (!*head)
		return (NULL);
	i = 0;
	flag = 0;
	str = NULL;
	tmp = *head;
	while (tmp)
	{
		token = tmp->data;
		if (!strcmp(token->type, "pipe"))
			flag = -1;
		else if (!strcmp(token->type, "space"))
		{
			if (str)
			{
				cmd[i] = str;
				i++;
				str = NULL;
			}
		}
		else
		{
			// concatenate str
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
	{
		cmd[i] = str;
	}
	*head = tmp;
	return (cmd);
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

void	cmd_execute(char *cmd, char **args, char **envp, t_history *history)
{
	int		i;
	// int		j;
	char	*cmd_;
	char	*path;
	t_llist	*paths;

	if (!strcmp(cmd, "cd"))
		return cd_cmd(args);
	else if (!strcmp(cmd, "echo"))
		return echo_cmd(args);
	else if (!strcmp(cmd, "env"))
		return env_cmd();
	else if (!strcmp(cmd, "exit"))
		return exit_cmd(args);
	else if (!strcmp(cmd, "export"))
		return export_cmd(args);
	else if (!strcmp(cmd, "pwd"))
		return pwd_cmd();
	else if (!strcmp(cmd, "unset"))
		return unset_cmd(args);
	else if (!strcmp(cmd, "history"))
		return show_history(history);
	i = 0;
	// j = strlen(args);
	while (1)
	{
		if (!strncmp(envp[i], "PATH=", 5))
			break;
		if (envp[i] == NULL)
			break;
		// printf("envp[%d] = %s\n", i, envp[i]);
		i++;
	}
	
	paths = ft_strsplit(&(envp[i])[5], ':');
	cmd_ = ft_strcat("/", cmd);
	path = cmd_access(paths, cmd_);
	free(cmd_);
	llist_free(&paths, ft_strfree);
	int	pid;
	pid = fork(); // TODO: how do they work?
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
    {
        execve(path, args, envp);
        perror(args[0]); // execve returns only if an error occurred
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
	// if (pid == 0)
	// 	execve(path, args, envp);
	waitpid(pid, NULL, WUNTRACED);
	free(path);
}
