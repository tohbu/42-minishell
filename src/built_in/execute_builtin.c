/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:25:37 by rseki             #+#    #+#             */
/*   Updated: 2025/05/21 12:06:22 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **argv, t_env_list *env, t_minishell *myshell)
{
	int	result;

	if (!argv || !argv[0])
		return (-1);
	if (ft_strcmp_builtin(argv[0], "echo") == 0)
		result = (ft_echo(argv, env));
	else if (ft_strcmp_builtin(argv[0], "pwd") == 0)
		result = (ft_pwd(argv, env));
	else if (ft_strcmp_builtin(argv[0], "env") == 0)
		result = (ft_env(argv, env));
	else if (ft_strcmp_builtin(argv[0], "exit") == 0)
		result = (ft_exit(argv, env, myshell));
	else if (ft_strcmp_builtin(argv[0], "cd") == 0)
		result = (ft_cd(argv, env));
	else if (ft_strcmp_builtin(argv[0], "export") == 0)
		result = (ft_export(argv, env));
	else if (ft_strcmp_builtin(argv[0], "unset") == 0)
		result = (ft_unset(argv, env));
	else
		result = (-1);
	free_args(argv);
	return (result);
}
