/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:05:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/29 13:48:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

char	*match_env_key(char *search, t_env_list *env)
{
	t_env_list	*tmp;

	tmp = env;
	printf("segf = %s\n", search);
	while (tmp)
	{
		if (strcmp(tmp->key, search) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_calloc(sizeof(char *), 1));
}

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

void	search_expand(t_command_list *com, t_env_list *env)
{
	t_command_list	*tmp_com;
	char			*result;
	char			*dast;

	tmp_com = com->next;
	while (tmp_com)
	{
		if ((tmp_com->token_type == WORD
				|| tmp_com->token_type == WORD_IN_DOUBLE_QOUTE)
			&& ft_strchr(tmp_com->s, '$'))
		{
			result = expand_command_str(tmp_com->s, env);
			while (result && ft_strchr(result, '$'))
			{
				dast = result;
				result = expand_command_str(result, env);
				free(dast);
			}
			dast = tmp_com->s;
			free(dast);
			tmp_com->s = result;
		}
		tmp_com = tmp_com->next;
	}
}

void	expand_env(t_tree *t, t_env_list *env)
{
	if (!t)
		return ;
	expand_env(t->left, env);
	expand_env(t->right, env);
	expand_herdoc(t->head);
	delete_quote_com(t->head);
	search_expand(t->head, env);
	return ;
}

void	print_env_list(t_env_list *t)
{
	while (t)
	{
		printf("key:%s value: %s\n", t->key, t->value);
		t = t->next;
	}
}
t_env_list	*get_envp_to_struct(char *envp[]) // dumy あり
{
	int i = 0;
	t_env_list *st_env;
	st_env = new_env_node(NULL, NULL);
	t_env_list *tmp = st_env;
	while (envp[i])
	{
		tmp->next = ft_get_env(envp[i]);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	return (st_env);
}

void	free_envlist(t_env_list *t)
{
	if (!t)
		return ;
	free_envlist(t->next);
	free(t->key);
	free(t->value);
	free(t);
}
