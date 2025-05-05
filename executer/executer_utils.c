/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:37:41 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 22:42:51 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_fd(void)
{
	int	i;

	i = STDERR_FILENO + 1;
	while (close(i) != -1)
		i++;
	return ;
}

t_bool	ft_strcmp_built_in(char *s)
{
	if (strcmp(s, "echo") == 0 || strcmp(s, "cd") == 0 || strcmp(s, "pwd") == 0
		|| strcmp(s, "export") == 0)
		return (1);
	if (strcmp(s, "unset") == 0 || strcmp(s, "env") == 0 || strcmp(s,
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

char	**vecter_join(char **array, char *s, int size)
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
		if (strcmp(tmp->key, "PATH") == 0)
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
