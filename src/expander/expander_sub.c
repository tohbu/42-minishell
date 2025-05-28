/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:19:26 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/28 19:13:15 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*result_expand_str(char *s, char *tmp, int state, t_env_list *env)
{
	int	j;

	if (*(++tmp) == '?')
	{
		return (join_last_status_with_back(ft_strndup(s, tmp - s - 1),
				ft_strdup(tmp + 1), state));
	}
	j = 0;
	while (check_env_format(tmp[j]))
		j++;
	return (join_env_vars_with_back(ft_strndup(s, tmp - s - 1), ft_strdup(tmp
				+ j), ft_strndup(tmp, j), env));
}

char	*scan_until_dollar(char *tmp, int *quote)
{
	while (*tmp && *tmp != '$')
	{
		if (*tmp == DOUBLE_QUOTE_CHAR)
			(*quote)++;
		if (*tmp == SINGLE_QUOTE_CHAR && (*quote % 2 == 0))
			tmp = skip_quotes(tmp, SINGLE_QUOTE_CHAR);
		if (!*tmp || *tmp == '$')
			break ;
		tmp++;
	}
	return (tmp);
}

char	*expand_env_or_status(char *s, t_env_list *env, int state, int i)
{
	char	*tmp;
	int		quote;

	tmp = s;
	quote = 0;
	while (i-- > 0)
	{
		tmp = scan_until_dollar(tmp, &quote);
		if (!*tmp)
			return (s);
		if (i > 0)
		{
			tmp++;
			continue ;
		}
		if (!check_env_format(*(tmp + 1)) && *(tmp + 1) != '?')
			return (s);
	}
	return (result_expand_str(s, tmp, state, env));
}
