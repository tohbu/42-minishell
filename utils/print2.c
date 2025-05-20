/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:59:55 by tohbu             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/08 21:56:42 by tomoki-kouk      ###   ########.fr       */
=======
/*   Updated: 2025/05/10 18:47:53 by tomoki-kouk      ###   ########.fr       */
>>>>>>> origin/main
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
	//t_tree_visualize(my_shell->ast, 0);
	printf("\n");
	//print_pid_list(my_shell->pid_list);
}
