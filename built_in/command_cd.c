/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:48:49 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 21:29:49 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static void	p_cd_error(const char *arg)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}

static void	p_cd_costum_error(const char *msg)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

static int	change_to_home(t_env_list **env)
{
	char	*old;
	char	*new;

	old = getcwd(NULL, 0);
	if (!old)
		return (1);
	chdir(match_env_key("HOME", *env));
	new = getcwd(NULL, 0);
	if (!new)
	{
		perror("cd: getcwd");
		return (free(old), 1);
	}
	ft_setenv(*env, "PWD", new);
	ft_setenv(*env, "OLDPWD", old);
	free(old);
	free(new);
	return (0);
}

/*
1. check if argument is given. if no return 0.
2. Get current working directory before change.
3. Change directory
4. Get new current directory after change
5. Update environment variables PWD and OLDPWD
*/
int	ft_cd(char **argv, t_env_list *env)
{
	char	*old;
	char	*new;

	if (!argv[1])
	{
		if (change_to_home(&env))
			return (perror("cd: getcwd"), 1);
		return (0);
	}
	if (argv[2])
		return (p_cd_costum_error("too many arguments"), 1);
	old = getcwd(NULL, 0);
	if (!old)
		return (perror("cd: getcwd"), 1);
	if (chdir(argv[1]) != 0)
	{
		p_cd_error(argv[1]);
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
