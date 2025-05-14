/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:48:49 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 15:06:40 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_cd(char **argv, t_env_list *env)
{
	char	*old;
	char	*new;

	if (!argv[1])
		return (p_builtin_error("cd", "missing argument"), 1);
	old = getcwd(NULL, 0);
	if (!old)
		return (perror("cd: getcwd"), 1);
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (free(old), 1);
	}
	new = getcwd(NULL, 0);
	if (!new)
	{
		perror("cd: getcwd");
		return (free(old), 1);
	}
	ft_setenv(env, "PWD", new);
	ft_setenv(env, "OLDPWD", old);
	free(old);
	free(new);
	return (0);
}
