/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:50:40 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 19:26:48 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pid_list	*new_pid_node(t_pid_list *head, pid_t p_id)
{
	t_pid_list	*new;
	t_pid_list	*tmp;

	tmp = head;
	new = (t_pid_list *)malloc(sizeof(t_pid_list));
	if (!new)
		return (NULL);
	new->pid = p_id;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (head);
}

t_pid_list	*init_pid_list(void)
{
	t_pid_list	*new;

	new = (t_pid_list *)malloc(sizeof(t_pid_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
