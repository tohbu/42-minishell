/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:09:33 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 15:06:40 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// Free
void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_env(t_env_list *env)
{
	t_env_list	*cur;
	t_env_list	*next;

	if (!env)
		return ;
	cur = env->next;
	while (cur)
	{
		next = cur->next;
		if (cur->key)
			free(cur->key);
		if (cur->value)
			free(cur->value);
		free(cur);
		cur = next;
	}
	free(env);
}
