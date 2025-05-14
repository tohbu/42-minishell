/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:03:57 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:44:52 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*init_node(void)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->head = malloc(sizeof(t_command_list));
	if (!new->head)
		return (free(new), NULL);
	new->head->next = NULL;
	new->head->s = NULL;
	new->token_type = 0;
	new->com = new->head;
	return (new);
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
