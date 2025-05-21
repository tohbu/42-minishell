/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_for_delete_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:34 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 11:22:36 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_single_quote(char *s, t_token_manager *token)
{
	char	*start;

	start = s++;
	while (*s && *s != '\'')
		s++;
	if (!*s)
		return (NULL);
	token->cur->next = add_list(ft_strndup(start, s - start + 1));
	return (s + 1);
}

char	*handle_double_quote(char *s, t_token_manager *token)
{
	char	*start;

	start = s++;
	while (*s && *s != '\"')
		s++;
	if (!*s)
		return (NULL);
	token->cur->next = add_list(ft_strndup(start, s - start + 1));
	return (s + 1);
}

char	*handle_word_for_expander(char *s, t_token_manager *token)
{
	char	*start;

	start = s;
	while (*s && !check_space(*s) && !check_meta_word(*s) && !check_quote(*s))
		s++;
	token->cur->next = add_list(ft_strndup(start, s - start));
	return (s);
}

t_bool	lexer_for_delete_quote(char *one_line, t_token_manager *token)
{
	while (*one_line)
	{
		while (*one_line && check_space(*one_line))
			one_line++;
		if (!*one_line)
			break ;
		if (check_meta_word(*one_line))
			one_line = handle_meta(one_line, token);
		else if (*one_line == '\'')
			one_line = handle_single_quote(one_line, token);
		else if (*one_line == '\"')
			one_line = handle_double_quote(one_line, token);
		else
			one_line = handle_word_for_expander(one_line, token);
		if (!one_line || !token->cur->next)
			return (ERROR);
		token->cur = token->cur->next;
	}
	token->cur = token->head->next;
	return (1);
}
