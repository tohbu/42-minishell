/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:19:26 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/15 18:19:36 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_same_char(char *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

char	*join_last_status_with_back(char *front, char *back, int state)
{
	char	*status;
	char	*res;

	if (g_interrupt_state)
		status = ft_itoa(g_interrupt_state + 128);
	else
		status = ft_itoa(state);
	res = ft_strjoin_and_free(front, status);
	res = ft_strjoin_and_free(res, back);
	return (res);
}

char	*join_env_vars_with_back(char *front, char *back, char *key,
		t_env_list *env)
{
	char	*result;

	result = ft_strjoin_and_free(front, match_env_key(key, env));
	result = ft_strjoin_and_free(result, back);
	free(key);
	return (result);
}

char	*expand_env_or_status(char *s, t_env_list *env, int state, int i)
{
	char	*tmp;
	char	*front;
	int		j;

	tmp = s;
	j = 0;
	while (i-- > 0)
	{
		while (*tmp && *tmp != '$')
			tmp++;
		if (!*tmp)
			return (s);
		if (i > 0 && tmp++)
			continue ;
		if (!check_env_format(*(tmp + 1)) && *(tmp + 1) != '?')
			return (s);
	}
	front = ft_strndup(s, (tmp++ - s));
	if (*tmp == '?')
		return (join_last_status_with_back(front, ft_strdup(tmp + 1), state));
	while (check_env_format(tmp[j]))
		j++;
	return (join_env_vars_with_back(front, ft_strdup(tmp + j), ft_strndup(tmp,
				j), env));
}
