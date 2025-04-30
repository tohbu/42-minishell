/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:46 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/29 17:01:42 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*delete_quote(char *s)
{
	char	*result;

	if (strcmp(s, "\"\"") == 0 || strcmp(s, "\'\'") == 0)
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
		if (tmp->token_type == WORD_IN_DOUBLE_QOUTE
			|| tmp->token_type == WORD_IN_SINGLE_QOUTE)
			tmp->s = delete_quote(tmp->s);
		tmp = tmp->next;
	}
}
