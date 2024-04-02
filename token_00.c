#include "minishell.h"

t_token	*token_create(char *text, char *type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->text = text;
	token->type = type;
	return (token);
}

void	token_free(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->text);
	free(token);
	// free(token->type);
}

void	token_print(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	printf("text: %s\n", token->text);
	printf("type: %s\n", token->type);
}
