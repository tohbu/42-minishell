/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:48:49 by rseki             #+#    #+#             */
/*   Updated: 2025/05/21 12:12:04 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand_tilde(const char *path, t_env_list *env)
{
	char		*home;
	char		*expanded;
	const char	*rest;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	home = match_env_key("HOME", env);
	if (!home)
		return (ft_strdup(path));
	if (path[1] == '/' || path[1] == '\0')
	{
		rest = path + 1;
		expanded = ft_strjoin(home, rest);
		return (expanded);
	}
	return (ft_strdup(path));
}

/*
0. check if argument is given. if 0, move to home.
1. check if the number of arguments is over 2.
2. Get current working directory before change.
3. check if path is with "~".
4. Change directory
5. Get new current directory after change
6. Update environment variables PWD and OLDPWD
*/
int	ft_cd(char **argv, t_env_list *env)
{
	char	*old;
	char	*path;
	char	*new;

	if (!argv[1])
		return (change_to_home(&env));
	if (argv[2])
		return (p_cd_costum_error("too many arguments"), 1);
	old = getcwd(NULL, 0);
	if (!old)
		return (perror("cd: getcwd"), 1);
	path = expand_tilde(argv[1], env);
	if (chdir(path) != 0)
		return (p_cd_error(argv[1]), free(old), free(path), 1);
	new = getcwd(NULL, 0);
	if (!new)
		return (perror("cd: getcwd"), free(old), 1);
	ft_setenv(env, "PWD", new);
	ft_setenv(env, "OLDPWD", old);
	free(path);
	free(old);
	free(new);
	return (0);
}
