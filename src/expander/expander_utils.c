/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:05:38 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/28 19:13:07 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	count_same_char(char *s, char c)
{
	int	count;
	int	double_quote;

	count = 0;
	double_quote = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == DOUBLE_QUOTE_CHAR)
			double_quote++;
		if (*s == SINGLE_QUOTE_CHAR && (double_quote % 2 == 0))
			s = skip_quotes(s, SINGLE_QUOTE_CHAR);
		else if (*s == c)
			count++;
		if (!*s)
			return (count);
		s++;
	}
	return (count);
}
