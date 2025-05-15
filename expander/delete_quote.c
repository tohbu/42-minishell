/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:46 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/15 14:50:16 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*delete_quote(char *s)
{
	char	*result;

	if (ft_strcmp(s, "\"\"") == 0 || ft_strcmp(s, "\'\'") == 0)
		result = ft_calloc(sizeof(char *), 1);
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}

void	delete_quote_com(t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com->next;
	while ((tmp))
	{
		if (tmp->token_type == HEARDOC)
			tmp = tmp->next;
		else if (tmp->token_type == WORD_IN_DOUBLE_QOUTE
			|| tmp->token_type == WORD_IN_SINGLE_QOUTE)
			tmp->s = delete_quote(tmp->s);
		tmp = tmp->next;
	}
}

char	*delete_quote_for_heredoc(char *s)
{
	char	*result;

	if (ft_strcmp(s, "\"\"") == 0 || ft_strcmp(s, "\'\'") == 0)
		result = ft_calloc(sizeof(char *), 1);
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}
