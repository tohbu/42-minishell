/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export_utilis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:40:16 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 15:06:40 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// 1. Count the environment list
static int	env_list_size(t_env_list *env)
{
	int			count;
	t_env_list	*tmp;

	count = 0;
	tmp = env->next;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

// 2. Convert to "KEY=\ "VALUE\"" string
static char	*format_export_entry(t_env_list *node)
{
	char	*formatted;
	char	*tmp;

	if (!node->value)
		return (ft_strdup(node->key));
	formatted = ft_strjoin(node->key, "=\"");
	if (!formatted)
		return (NULL);
	tmp = ft_strjoin(formatted, node->value);
	free(formatted);
	if (!tmp)
		return (NULL);
	formatted = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!formatted)
		return (NULL);
	return (formatted);
}

// 3. Convert to array
static char	**env_list_to_array(t_env_list *env)
{
	int			size;
	char		**array;
	t_env_list	*tmp;
	int			i;

	size = env_list_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	tmp = env->next;
	i = 0;
	while (tmp)
	{
		array[i++] = format_export_entry(tmp);
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

// 4. Sort the array
static void	sort_string_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

// 5. combine into convert_env_list_to_sorted_array
char	**convert_env_list_to_sorted_array(t_env_list *env)
{
	char **array;

	array = env_list_to_array(env);
	if (!array)
		return (NULL);
	sort_string_array(array);
	return (array);
}