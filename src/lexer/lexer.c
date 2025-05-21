/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:49:19 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:16:44 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_meta(char *s, t_token_manager *token)
{
	int	len;

	len = 1;
	if (*s == '&' && *(s + 1) != '&')
		return (NULL);
	if ((*s == '<' && *(s + 1) == '<') || (*s == '>' && *(s + 1) == '>')
		|| (*s == '&' && *(s + 1) == '&') || (*s == '|' && *(s + 1) == '|'))
		len = 2;
	token->cur->next = add_list(ft_strndup(s, len));
	return (s + len);
}

char	*handle_word(char *s, t_token_manager *token, int e_flag)
{
	char	*start;

	start = s;
	while (*s && !check_space(*s) && !check_meta_word(*s))
	{
		if (*s == SINGLE_QUOTE_CHAR)
		{
			s++;
			while (*s && *s != SINGLE_QUOTE_CHAR)
				s++;
		}
		else if (*s == DOUBLE_QUOTE_CHAR)
		{
			s++;
			while (*s && *s != DOUBLE_QUOTE_CHAR)
				s++;
		}
		if (!*s && ++e_flag)
			break ;
		s++;
	}
	token->cur->next = add_list(ft_strndup(start, s - start));
	token->cur->next->error_flag = e_flag;
	return (s);
}

t_bool	lexer(char *one_line, t_token_manager *token)
{
	while (*one_line)
	{
		while (*one_line && check_space(*one_line))
			one_line++;
		if (!*one_line)
			break ;
		if (check_meta_word(*one_line))
			one_line = handle_meta(one_line, token);
		else
			one_line = handle_word(one_line, token, 0);
		if (!token->cur->next)
			return (ERROR);
		token->cur = token->cur->next;
	}
	token->cur = token->head->next;
	return (1);
}
