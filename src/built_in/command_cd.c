/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:48:49 by rseki             #+#    #+#             */
/*   Updated: 2025/05/29 14:54:03 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	change_to_home(t_env_list **env)
{
	char	*old;
	char	*home;

	home = get_home_path(*env);
	if (!home)
		return (1);
	old = get_old_pwd(*env);
	return (change_dir_to_home(home, old, env));
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

static int	change_dir(const char *dir, t_env_list *env, \
	char **oldpwd, char **newpwd)
{
	char	*path;
	char	*fallback;

	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
	{
		fallback = match_env_key("PWD", env);
		if (fallback)
			*oldpwd = ft_strdup(fallback);
		else
			*oldpwd = ft_strdup("");
	}
	path = expand_tilde(dir, env);
	if (chdir(path) != 0)
		return (p_cd_error(dir), free(*oldpwd), free(path), free(fallback), 1);
	free(path);
	free(fallback);
	*newpwd = getcwd(NULL, 0);
	if (!*newpwd)
		*newpwd = ft_strdup(dir);
	return (0);
}

/*
0. check if argument is given. if 0, move to home.
1. check if the number of arguments is over 2.
2. Get current working directory before change.
3. check if path is with "~" by expand_tilde.
4. Change directory by chdir
5. Get new current directory after change
6. Update environment variables PWD and OLDPWD
*/
int	ft_cd(char **argv, t_env_list *env)
{
	char	*old;
	char	*new;

	if (!argv[1])
		return (change_to_home(&env));
	if (argv[2])
		return (p_cd_costum_error("too many arguments"), 1);
	if (change_dir(argv[1], env, &old, &new))
		return (1);
	ft_setenv(env, "PWD", new);
	ft_setenv(env, "OLDPWD", old);
	free(old);
	free(new);
	return (0);
}
