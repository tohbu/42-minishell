/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:45:33 by rseki             #+#    #+#             */
/*   Updated: 2025/05/29 14:45:02 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

void	p_cd_error(const char *arg)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}

void	p_cd_costum_error(const char *msg)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

char	*get_old_pwd(t_env_list *env)
{
	char	*old;

	old = getcwd(NULL, 0);
	if (!old)
	{
		old = match_env_key("PWD", env);
		if (old)
			old = ft_strdup(old);
		else
			old = ft_strdup("");
	}
	return (old);
}

char	*get_home_path(t_env_list *env)
{
	char	*home;

	home = match_env_key("HOME", env);
	if (!home || *home == '\0')
	{
		p_cd_costum_error("HOME not set");
		return (NULL);
	}
	home = ft_strdup(home);
	if (!home)
		p_cd_costum_error("malloc failed");
	return (home);
}

int	change_dir_to_home(char *home, char *old, t_env_list **env)
{
	char	*new;

	if (chdir(home) != 0)
	{
		p_cd_error(home);
		free(old);
		free(home);
		return (1);
	}
	new = getcwd(NULL, 0);
	if (!new)
		new = ft_strdup(home);
	ft_setenv(*env, "OLDPWD", old);
	ft_setenv(*env, "PWD", new);
	free(old);
	free(new);
	free(home);
	return (0);
}
