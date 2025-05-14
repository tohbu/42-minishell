/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:05:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:54:32 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_command_str(char *s, t_env_list *env)
{
	char	*tmp;
	int		i;
	char	*front;
	char	*back;
	char	*result;

	tmp = s;
	i = 0;
	while (*tmp && *tmp != '$')
		tmp++;
	if (!*tmp || !*(tmp + 1))
		return (s);
	front = ft_strndup(s, (tmp++ - s));
	while (check_env_format(tmp[i]))
		i++;
	back = ft_strdup(tmp + i);
	tmp = ft_strndup(tmp, i);
	result = ft_strjoin_and_free(front, match_env_key(tmp, env));
	result = ft_strjoin_and_free(result, back);
	free(tmp);
	return (result);
}

void	expand_env_vars(t_command_list *com, t_env_list *env)
{
	t_command_list	*tmp_com;
	char			*result;
	char			*dast;

	tmp_com = com->next;
	while (tmp_com)
	{
		if ((tmp_com->token_type == WORD
				|| tmp_com->token_type == WORD_IN_DOUBLE_QOUTE)
			&& ft_strchr(tmp_com->s, '$'))
		{
			result = expand_command_str(tmp_com->s, env);
			while (result && ft_strchr(result, '$'))
			{
				dast = result;
				result = expand_command_str(result, env);
				free(dast);
			}
			dast = tmp_com->s;
			free(dast);
			tmp_com->s = result;
		}
		tmp_com = tmp_com->next;
	}
}

void	expand_env(t_tree *t, t_minishell *my_shell)
{
	if (!t)
		return ;
	expand_env(t->left, my_shell);
	expand_env(t->right, my_shell);
	delete_quote_com(t->head);
	expand_last_state(t->head, my_shell);
	expand_env_vars(t->head, my_shell->env->next);
	return ;
}

char	*match_env_key(char *search, t_env_list *env)
{
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, search) == 0)
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
