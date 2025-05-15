/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:37:41 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/15 14:50:20 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	close_all_fd(void)
{
	int	i;

	i = STDERR_FILENO + 1;
	while (close(i) != -1)
		i++;
	return (1);
}

t_bool	ft_strcmp_built_in(char *s)
{
	if (ft_strcmp(s, "echo") == 0 || ft_strcmp(s, "cd") == 0 || ft_strcmp(s,
			"pwd") == 0 || ft_strcmp(s, "export") == 0)
		return (1);
	if (ft_strcmp(s, "unset") == 0 || ft_strcmp(s, "env") == 0 || ft_strcmp(s,
			"exit") == 0)
		return (1);
	return (0);
}

t_bool	is_built_in(t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com;
	while (tmp)
	{
		if (REDIRECT_IN <= tmp->token_type && tmp->token_type <= HEARDOC)
			tmp = tmp->next;
		else
			return (ft_strcmp_built_in(tmp->s));
		tmp = tmp->next;
	}
	return (0);
}

char	**join_argv(char **array, char *s, int size)
{
	char	**reslut;
	int		i;

	reslut = (char **)malloc(sizeof(char *) * (size + 1));
	if (!reslut)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		reslut[i] = array[i];
		i++;
	}
	reslut[i++] = ft_strdup(s);
	reslut[i] = NULL;
	if (array)
		free(array);
	return (reslut);
}

char	**get_path(t_env_list *env)
{
	char		**reslut;
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	reslut = ft_split(tmp->value, ':');
	if (!reslut)
		return (NULL);
	return (reslut);
}
