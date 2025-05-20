/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:58:29 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 21:30:43 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && (arg[0] != '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*remove_surrounding_quates(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

static void	handle_export_arg(const char *arg, t_env_list *env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	char	*clean_value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		ft_setenv(env, arg, "");
	else
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		clean_value = remove_surrounding_quates(value);
		ft_setenv(env, key, clean_value);
		free(clean_value);
		free(key);
		free(value);
	}
}

static int	print_export_list(t_env_list *env)
{
	char	**sorted;
	int		i;

	sorted = convert_env_list_to_sorted_array(env);
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sorted[i], 1);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

int	ft_export(char **argv, t_env_list *env)
{
	int		i;
	int		ret;
	char	*key;
	char	*equal_sign;

	ret = 0;
	if (!argv[1])
		return (print_export_list(env));
	i = 1;
	while (argv[i])
	{
		equal_sign = ft_strchr(argv[i], '=');
		if (equal_sign)
			key = ft_substr(argv[i], 0, equal_sign - argv[i]);
		else
			key = ft_strdup(argv[i]);
		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			handle_export_arg(argv[i], env);
		free(key);
		i++;
	}
	return (ret);
}
