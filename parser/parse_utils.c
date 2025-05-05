/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:03:57 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 19:25:48 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	p_t_command_list(t_command_list *com)
{
	int				i;
	t_command_list	*tmp;

	i = 0;
	if (!com)
	{
		return ;
	}
	tmp = com;
	while (tmp != NULL)
	{
		printf("%d:%s	", i++, tmp->s);
		tmp = tmp->next;
	}
}

t_command_list	*new_t_command_list(char *str, int type)
{
	t_command_list	*new;

	new = (t_command_list *)malloc(sizeof(t_command_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->s = ft_strdup(str);
	new->token_type = type;
	return (new);
}

t_tree	*new_node(t_tree *l, t_tree *r, int t_type, char *s)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->token_type = t_type;
	new->left = l;
	new->right = r;
	new->head = (t_command_list *)malloc(sizeof(t_command_list));
	new->head->s = NULL;
	new->head->next = new_t_command_list(s, t_type);
	new->com = new->head->next;
	return (new);
}

t_bool	is_token_word(t_token_list *t)
{
	if (t->token_type == WORD || t->token_type == WORD_IN_DOUBLE_QOUTE
		|| t->token_type == WORD_IN_SINGLE_QOUTE)
		return (1);
	else
		return (0);
}

t_bool	syntax_check(t_token_all *all, t_tree *t)
{
	t_token_list	*tmp;

	tmp = all->head->next;
	while (tmp)
	{
		if (tmp->error_flag == SYNTAX_ERROR)
		{
			if (!tmp->next)
			{
				printf("minishell:");
				printf(" syntax error near unexpected token \'newline\'\n");
			}
			else
				printf("minishell: syntax error near unexpected token \'%s\'\n",
					tmp->token);
			free_all(all, t);
			return (0);
		}
		if (tmp->error_flag == SIGINT)
			return (free_all(all, t), 0);
		tmp = tmp->next;
	}
	return (1);
}
