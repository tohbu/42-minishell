/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:35:07 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/28 19:10:12 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_token_word(t_token_list *t)
{
	if (t->token_type == WORD || t->token_type == WORD_IN_DOUBLE_QOUTE
		|| t->token_type == WORD_IN_SINGLE_QOUTE)
		return (1);
	else
		return (0);
}

t_bool	set_syntax_error(t_token_manager *token)
{
	t_token_list	*tmp;

	tmp = token->head->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->error_flag = SYNTAX_ERROR;
	return (1);
}

t_bool	syntax_check(t_token_manager *token, t_tree *t)
{
	t_token_list	*tmp;

	(void)t;
	tmp = token->head->next;
	while (tmp)
	{
		if (tmp->error_flag == UN_CLOSE_QUOTE)
			return (printf("minishell: syntax error  unclosed quote\n"), 0);
		if (tmp->error_flag == SYNTAX_ERROR)
		{
			if (!tmp->next)
			{
				printf("minishell:");
				printf(" syntax error near unexpected token \'newline\'\n");
			}
			else
				printf("minishell: syntax error near unexpected token \'%s\'\n",
					tmp->token);
			return (0);
		}
		if (tmp->error_flag == SIGINT)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}
