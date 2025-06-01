/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:20:34 by rseki             #+#    #+#             */
/*   Updated: 2025/05/29 14:53:26 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	too_many_argument(char **argv)
{
	if (argv[1])
	{
		p_builtin_error("pwd", "too many arguments");
		return (1);
	}
	return (0);
}

int	ft_pwd(char **argv, t_env_list *env)
{
	char	cwd[BUFSIZ];
	char	*pwd;

	pwd = NULL;
	if (too_many_argument(argv))
		return (1);
	if (getcwd(cwd, sizeof(cwd)))
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		pwd = match_env_key("PWD", env);
		if (pwd && *pwd)
		{
			write(STDOUT_FILENO, pwd, ft_strlen(pwd));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
			return (perror("pwd: getcwd"), 1);
	}
	free(pwd);
	return (0);
}
