#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_llist
{
	void			*data;
	struct s_llist	*prev;
	struct s_llist	*next;
}	t_llist;

typedef struct s_token
{
	char	*text;
	char	*type;
}	t_token;

// ft_func.c
int				ft_strlen(char *str);
int				ft_strlen_to_char(char *str, char c);
int				ft_strlen_to_space(char *str);
int				ft_strlen_to_next(char *str);

t_llist			*ft_strsplit(char *str, char delimiter);
char			*ft_strget(char *str, int start, int end);
char			*ft_strcat(char *str1, char *str2);
void			ft_strprint(void *data);

int				ft_isspace(char c);
int				ft_isredir(char c);
int				ft_isquote(char c);
int				ft_islogic(char c);

// signal_*.c
void			signal_handler(int signal);

// parser_*.c
t_llist			*parser(char *str);
char			**get_cmd(t_llist **tokens);
int				get_cmd_len(t_llist **tokens);

// llist_00.c
t_llist			*llist_create(void *data);
void			llist_add(t_llist **head, t_llist *node);
t_llist			*llist_del(t_llist **head);
void			llist_free(t_llist **head, void(*free_data)(void *));

// llist_01.c
int				llist_len(t_llist *head);
void			llist_print(t_llist *head, void(*print_data)(void *));

// token_00.c
t_token			*token_create(char *token, char *type);
void			token_print(void *data);
void			token_free(void *data);

// string_00.c
char			**string_2d_init(int n);
void			string_2d_free(char **str, int n);

#endif
