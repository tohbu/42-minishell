/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:19:26 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 20:27:06 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_last_state(t_command_list *com, t_minishell *my_shell)
{
	t_command_list	*tmp_com;
	char			*reslut;
	char			*dast;

	tmp_com = com->next;
	while (tmp_com)
	{
		if ((tmp_com->token_type == WORD
				|| tmp_com->token_type == WORD_IN_DOUBLE_QOUTE)
			&& ft_strchr(tmp_com->s, '$'))
		{
			reslut = expand_last_state_sub(tmp_com->s, my_shell);
			if (reslut != tmp_com->s)
				free(tmp_com->s);
			while (reslut && ft_strchr(reslut, '$'))
			{
				dast = reslut;
				reslut = expand_last_state_sub(reslut, my_shell);
				if (dast != reslut)
					free(dast);
				else
					break ;
			}
			tmp_com->s = reslut;
		}
		tmp_com = tmp_com->next;
	}
}

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
