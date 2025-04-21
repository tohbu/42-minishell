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