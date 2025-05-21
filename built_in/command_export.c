/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:58:29 by rseki             #+#    #+#             */
/*   Updated: 2025/05/21 11:34:33 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static char	*get_export_key(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		return (ft_substr(arg, 0, equal_sign - arg));
	else
		return (ft_strdup(arg));
}

static int	is_invalid_identifier(char *key, char *arg)
{
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	return (0);
}

static int	process_export_arg(char *arg, t_env_list *env)
{
	char	*key;
	int		ret;

	key = get_export_key(arg);
	if (!key)
		return (1);
	ret = is_invalid_identifier(key, arg);
	if (!ret)
		handle_export_arg(arg, env);
	free(key);
	return (ret);
}

int	ft_export(char **argv, t_env_list *env)
{
	int	i;
	int	ret;

	ret = 0;
	if (!argv[1])
		return (print_export_list(env));
	i = 1;
	while (argv[i])
	{
		if (process_export_arg(argv[i], env))
			ret = 1;
		i++;
	}
	return (ret);
}
