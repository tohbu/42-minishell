/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:49:06 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/18 17:21:45 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	check_meta_word(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
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
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, "||") == 0)
		return (OR);
	else if (ft_strcmp(s, "&&") == 0)
		return (AND);
	else if (ft_strcmp(s, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(s, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(s, "<<") == 0)
		return (HEARDOC);
	else if (ft_strcmp(s, ">>") == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}
