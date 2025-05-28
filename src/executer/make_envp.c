/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:26:13 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/28 18:38:11 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_envp(t_env_list *env)
{
	char	**result;
	char	*tmp;
	int		i;

	result = NULL;
	i = 1;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		tmp = ft_strjoin_and_free(tmp, ft_strdup(env->value));
		result = join_argv(result, tmp, i++);
		free(tmp);
		env = env->next;
	}
	return (result);
}
