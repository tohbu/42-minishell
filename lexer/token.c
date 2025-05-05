/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:49:19 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 20:05:14 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_all	*init_t_token_all(void)
{
	t_token_all	*all;

	all = (t_token_all *)malloc(sizeof(t_token_all));
	all->head = (t_token_list *)malloc(sizeof(t_token_list));
	if (!all->head)
		return (NULL);
	all->cur = all->head;
	all->pipe_n = 0;
	all->head->token = NULL;
	all->head->token_type = 0;
	all->head->error_flag = 0;
	return (all);
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

t_bool	lexer(char *one_line, t_token_all *all)
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
				all->cur->next = add_list(ft_strndup(one_line, 2));
				one_line++;
			}
			else if (*one_line == '>' && *(one_line + 1) == '>')
			{
				all->cur->next = add_list(ft_strndup(one_line, 2));
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
	return (1);
}
