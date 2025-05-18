/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:05:38 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/18 20:01:00 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*reslut;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	reslut = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!reslut)
		return (NULL);
	while (s1[i])
	{
		reslut[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		reslut[i + j] = s2[j];
		j++;
	}
	reslut[i + j] = '\0';
	free(s1);
	free(s2);
	return (reslut);
}

t_bool	check_env_format(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
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

t_env_list	*new_env_node(char *in_key, char *in_value)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->key = in_key;
	new->value = in_value;
	new->next = NULL;
	return (new);
}

t_env_list	*ft_get_env(char *s)
{
	char	*key;
	char	*value;

	if (!*s)
		return (NULL);
	key = ft_strndup(s, ft_strchr(s, '=') - s);
	value = ft_strdup(ft_strchr(s, '=') + 1);
	return (new_env_node(key, value));
}

char	*expand_command_str(char *s, t_env_list *env)
{
	char	*tmp;
	int		i;
	char	*front;
	char	*back;
	char	*result;

	tmp = s;
	i = 0;
	while (*tmp && *tmp != '$')
		tmp++;
	if (!*tmp || !*(tmp + 1))
		return (s);
	front = ft_strndup(s, (tmp++ - s));
	while (check_env_format(tmp[i]))
		i++;
	back = ft_strdup(tmp + i);
	tmp = ft_strndup(tmp, i);
	result = ft_strjoin_and_free(front, match_env_key(tmp, env));
	result = ft_strjoin_and_free(result, back);
	free(tmp);
	return (result);
}



