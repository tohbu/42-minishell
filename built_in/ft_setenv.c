/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:53:13 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 15:06:40 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static void	free_content(t_env_list **node)
{
	if (!node || !*node)
		return ;
	free((*node)->key);
	free((*node)->value);
	free(*node);
	*node = NULL;
}

// Try to update existing key.
static int	update_value(t_env_list *env, const char *key, char *value)
{
	char	*new_value;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (1);
			free(env->value);
			env->value = new_value;
			return (0);
		}
		env = env->next;
	}
	return (1);
}

// Updates the env if exists(update_value()), or adds it if missing
int	ft_setenv(t_env_list *env, const char *key, char *value)
{
	t_env_list	*new;

	if (update_value(env, key, value) == 0)
		return (0);
	new = malloc(sizeof(t_env_list));
	if (!new)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
		return (free_content(&new), 1);
	new->next = env->next;
	env->next = new;
	return (0);
}
