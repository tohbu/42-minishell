/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:46 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/19 10:59:37 by tomoki-kouk      ###   ########.fr       */
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

char	*strjoin_token_list(t_token_list *tokne_list)
{
	char			*result;
	char			*pre;
	t_token_list	*tmp;

	tmp = tokne_list;
	result = ft_strdup(tmp->token);
	while (tmp->next)
	{
		pre = result;
		result = ft_strjoin(pre, tmp->next->token);
		free(pre);
		tmp = tmp->next;
	}
	return (result);
}

char	*delete_quote_sub(char *com, t_token_manager *token_mg)
{
	t_token_list	*tmp;
	char			*result;

	lexer_for_delete_quote(com, token_mg);
	tmp = token_mg->head->next;
	while (tmp)
	{
		if (ft_strchr(tmp->token, SINGLE_QUOTE_CHAR) || ft_strchr(tmp->token,
				DOUBLE_QUOTE_CHAR))
			tmp->token = delete_quote(tmp->token);
		tmp = tmp->next;
	}
	result = strjoin_token_list(token_mg->head->next);
	free(com);
	free_t_token_manager(token_mg);
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
		else if (tmp->token_type == WORD)
			tmp->s = delete_quote_sub(tmp->s, init_t_token_manager());
		tmp = tmp->next;
	}
}
