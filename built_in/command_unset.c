/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:56:27 by rseki             #+#    #+#             */
/*   Updated: 2025/05/13 18:56:28 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	remove_env_entry(t_env_list **env, const char *key)
{
	t_env_list	*cur;
	t_env_list	*prev;

	if (!env || !*env || !key)
		return ;
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			if (cur->value)
				free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/*
unset VAR
	->Removes VAR if it exists in env list
unset VAR1 VAR2 ...
	->Can accept multiple arguments
Invalid identifiers (e.g., 1VAR)
	->Should ignore silently or print error, does not unset anything
If the variable does not exist
	->	Does nothing silently
*/
int	ft_unset(char **argv, t_env_list *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			remove_env_entry(&env, argv[i]);
		else
			p_builtin_error("unset", "Invalid identifier");
		i++;
	}
	return (0);
}
