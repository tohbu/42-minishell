/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export_utilis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:56 by rseki             #+#    #+#             */
/*   Updated: 2025/05/21 12:00:05 by rseki            ###   ########.fr       */
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

void	handle_export_arg(const char *arg, t_env_list *env)
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

int	print_export_list(t_env_list *env)
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
