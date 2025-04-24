
#include "lexer.h"


token_all* init_token_all(token_all *all)
{
	if(!all)
		return NULL;
	all->head =(token_list*)malloc(sizeof(token_list));
	if(!all->head)
		return NULL;
	all->cur  = all->head;
	all->pipe_n = 0;
	all->head->token = NULL;
	all->head->token_type = 0;
	all->head->syntax_error = 0;
	return all;
}

token_list	*add_list(char *s)
{
	token_list	*new;


	new = (token_list *)malloc(sizeof(token_list));
	if (!new || !s)
		return (NULL);
	new->token = s;
	if(!new->token)
		return NULL;
	new->token_type = get_token_type(s);
	new->syntax_error = 0;
	new->next = NULL;
	return (new);
}

t_bool	lexer(char *one_line, token_all *all)
{
	char	*start;

	while (*one_line)
	{
		while (*one_line && check_space(*one_line))
			one_line++;
		if (!*one_line)
			break ;
		if (check_meta_word(*one_line)) // and  or	もこの中で処理を行う
		{
			if (*one_line == '|')
				all->pipe_n++;
			if (*one_line == '<' && *(one_line + 1) == '<')
			{
				all->cur->next = add_list(ft_strndup(one_line, 2)); // << を処理
				one_line++;
			}
			else if (*one_line == '>' && *(one_line + 1) == '>')
			{
				all->cur->next = add_list(ft_strndup(one_line, 2)); // >> を処理
				one_line++;
			}
			else
				all->cur->next = add_list(ft_strndup(one_line, 1));
			one_line++;
		}
		else if (*one_line == '\'')
		{
			start = one_line;
			one_line++;
			while (*one_line && *one_line != '\'')
				one_line++;
			if (!*one_line)
				return (ERROR);
			all->cur->next = add_list(ft_strndup(start, one_line - start + 1));
			one_line++;
		}
		else if (*one_line == '\"')
		{
			start = one_line;
			one_line++;
			while (*one_line && *one_line != '\"')
				one_line++;
			if (!*one_line)
				return (ERROR);
			all->cur->next = add_list(ft_strndup(start, one_line - start + 1));
			one_line++;
		}
		else
		{
			start = one_line;
			while (*one_line && !check_space(*one_line)
				&& !check_meta_word(*one_line) && !check_quote(*one_line))
				one_line++;
			all->cur->next = add_list(ft_strndup(start, one_line - start));
		}
		if (!all->cur->next)
			return (ERROR);
		all->cur = all->cur->next;
	}
	all->cur = all->head->next;
	return 1;
}
