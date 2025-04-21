
#include "lexer.h"

t_bool	check_meta_word(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_bool	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

t_bool	check_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(n + 1);
	if (!ret)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	get_token_type(char *s)
{
	if (ft_strchr(s, '\''))
		return (WORD_IN_SINGLE_QOUTE);
	else if (ft_strchr(s, '\"'))
		return (WORD_IN_DOUBLE_QOUTE);
	else if (strcmp(s, "|") == 0)
		return (PIPE);
	else if (strcmp(s, "<") == 0 || strcmp(s, ">") == 0)
		return (REDIRECT);
	else if (strcmp(s, "<<") == 0)
		return (HEARDOC);
	else if (strcmp(s, ">>") == 0)
		return (REDIRECT);
	return (WORD);
}

token_all* init_token_all(token_all *all)
{
	all->head =(token_list*)malloc(sizeof(token_list));
	all->cur  = all->head;
	all->pipe_n = 0;
	return all;
}




token_list	*add_list(char *s)
{
	token_list	*new;

	new = (token_list *)malloc(sizeof(token_list));
	if (!new)
		return (NULL);
	new->token = s;
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
		if (check_meta_word(*one_line))
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
