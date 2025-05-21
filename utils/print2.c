/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:59:55 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 11:34:09 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_t_command_list(t_command_list *com)
{
	int				i;
	t_command_list	*tmp;

	i = 0;
	if (!com)
	{
		printf("com = NULL\n");
		return ;
	}
	tmp = com;
	while (tmp)
	{
		printf("%d:%s	", i++, tmp->s);
		tmp = tmp->next;
	}
}

void	print_pid_list(t_pid_list *pid_list)
{
	t_pid_list	*tmp;
	int			i;

	i = 0;
	tmp = pid_list->next;
	while (tmp)
	{
		printf("pid[%d] = %d\n", i, tmp->pid);
		tmp = tmp->next;
	}
	return ;
}

void	print_env_list(t_env_list *t)
{
	while (t)
	{
		printf("key:%s value: %s\n", t->key, t->value);
		t = t->next;
	}
}

void	print_debag(t_minishell *my_shell)
{
	printf("\n-------------------debug----------------\n");
	print_t_token_list(my_shell->token->head->next);
	printf("\n");
}
