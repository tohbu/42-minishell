/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:23:31 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 15:06:40 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_env(char **argv, t_env_list *env)
{
	if (argv[1])
	{
		p_builtin_error("env", "no option or argument avaiable");
		return (1);
	}
	env = env->next;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
