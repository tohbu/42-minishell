/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:05:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/18 17:48:01 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*match_env_key(char *search, t_env_list *env)
{
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_calloc(sizeof(char *), 1));
}

t_env_list	*get_envp_to_struct(char *envp[])
{
	int			i;
	t_env_list	*st_env;
	t_env_list	*tmp;

	i = 0;
	st_env = new_env_node(NULL, NULL);
	tmp = st_env;
	while (envp[i])
	{
		tmp->next = ft_get_env(envp[i]);
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	return (st_env);
}

char	*expand_all_dollars(char *s, t_env_list *env, int state)
{
	int		count;
	char	*pre;
	char	*cur;
	int		i;

	count = count_same_char(s, '$');
	pre = s;
	cur = s;
	i = 1;
	while (count-- > 0)
	{
		cur = expand_env_or_status(pre, env, state, i);
		if (cur == pre)
		{
			i++;
			continue ;
		}
		free(pre);
		pre = cur;
	}
	return (cur);
}

void	expand_env_args_and_state(t_command_list *com, t_env_list *env,
		int state)
{
	t_command_list	*cur;

	cur = com->next;
	while (cur)
	{
		if (cur->token_type == WORD && ft_strchr(cur->s, '$'))
		{
			cur->s = expand_all_dollars(cur->s, env, state);
		}
		cur = cur->next;
	}
}

void	expand_env(t_tree *t, t_minishell *my_shell)
{
	if (!t)
		return ;
	expand_env(t->left, my_shell);
	expand_env(t->right, my_shell);
	expand_env_args_and_state(t->head, my_shell->env->next, my_shell->state);
	delete_quote_com(t->head);
	return ;
}
