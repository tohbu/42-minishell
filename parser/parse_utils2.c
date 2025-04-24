/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:03:08 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/24 22:18:28 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

t_bool	set_syntax_error(t_token_all *all)
{
	t_token_list	*tmp;

	tmp = all->head->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->syntax_error = 1;
	return (1);
}
