/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:49:19 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 21:38:49 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_manager	*init_t_token_manager(void)
{
	t_token_manager	*token;

	token = (t_token_manager *)malloc(sizeof(t_token_manager));
	token->head = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token->head)
		return (NULL);
	token->cur = token->head;
	token->head->token = NULL;
	token->head->next = NULL;
	token->head->token_type = 0;
	token->head->error_flag = 0;
	return (token);
}

t_token_list	*add_list(char *s)
{
	t_token_list	*new;

	new = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new || !s)
		return (NULL);
	new->token = s;
	if (!new->token)
		return (NULL);
	new->token_type = get_token_type(s);
	new->error_flag = 0;
	new->next = NULL;
	return (new);
}

t_bool	lexer(char *one_line, t_token_manager *token)
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
			if (*one_line == '<' && *(one_line + 1) == '<')
			{
				token->cur->next = add_list(ft_strndup(one_line, 2));
				one_line++;
			}
			else if (*one_line == '>' && *(one_line + 1) == '>')
			{
				token->cur->next = add_list(ft_strndup(one_line, 2));
				one_line++;
			}
			else
				token->cur->next = add_list(ft_strndup(one_line, 1));
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
			token->cur->next = add_list(ft_strndup(start, one_line - start
						+ 1));
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
			token->cur->next = add_list(ft_strndup(start, one_line - start
						+ 1));
			one_line++;
		}
		else
		{
			start = one_line;
			while (*one_line && !check_space(*one_line)
				&& !check_meta_word(*one_line) && !check_quote(*one_line))
				one_line++;
			token->cur->next = add_list(ft_strndup(start, one_line - start));
		}
		if (!token->cur->next)
			return (ERROR);
		token->cur = token->cur->next;
	}
	token->cur = token->head->next;
	return (1);
}
