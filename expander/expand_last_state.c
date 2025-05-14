/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:19:26 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:56:17 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_last_state_sub(char *s, t_minishell *my_shell)
{
	char	*tmp;
	char	*result;
	char	*front;
	char	*back;

	tmp = s;
	while (*tmp && *tmp != '$')
		tmp++;
	if (!*tmp || *(tmp + 1) != '?')
		return (s);
	front = ft_strndup(s, (tmp++ - s));
	back = ft_strdup(tmp + 1);
	if (g_interrupt_state)
		result = ft_strjoin_and_free(front, ft_itoa(g_interrupt_state + 128));
	else
		result = ft_strjoin_and_free(front, ft_itoa(my_shell->state));
	result = ft_strjoin_and_free(result, back);
	return (result);
}

static void	update_expanded_str(t_command_list *com, t_minishell *sh)
{
	char	*res;
	char	*tmp;

	res = expand_last_state_sub(com->s, sh);
	if (res != com->s)
		free(com->s);
	while (res && ft_strchr(res, '$'))
	{
		tmp = res;
		res = expand_last_state_sub(res, sh);
		if (tmp == res)
			break ;
		free(tmp);
	}
	com->s = res;
}

void	expand_last_state(t_command_list *com, t_minishell *sh)
{
	t_command_list	*cur;

	cur = com->next;
	while (cur)
	{
		if ((cur->token_type == WORD || cur->token_type == WORD_IN_DOUBLE_QOUTE)
			&& ft_strchr(cur->s, '$'))
			update_expanded_str(cur, sh);
		cur = cur->next;
	}
}
