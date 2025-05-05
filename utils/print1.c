/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:35:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 23:21:17 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tab(int n)
{
	while (n-- > 0)
		printf("     ");
}

void	print_token(int t, t_command_list *head)
{
	t_command_list	*tmp;

	tmp = head->next;
	if (t == PIPE)
		printf("(PIPE)");
	else
		printf("COMMAND");
	while (tmp)
	{
		printf("[%s]", tmp->s);
		tmp = tmp->next;
	}
}

void	t_tree_visualize(t_tree *t, int deep)
{
	if (!t)
		return ;
	print_token(t->token_type, t->head);
	if (t->right)
		printf("--↓--");
	t_tree_visualize(t->right, deep + 1);
	printf("\n");
	print_tab(deep + 1);
	t_tree_visualize(t->left, deep + 1);
}

char	*print_type(int token_type)
{
	if (token_type == PIPE)
		return ("PIPE");
	else if (token_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (token_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (token_type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (token_type == HEARDOC)
		return ("HEARDOC");
	else if (token_type == WORD_IN_SINGLE_QOUTE)
		return ("WORD_IN_SINGLE_QOUTE");
	else if (token_type == WORD_IN_DOUBLE_QOUTE)
		return ("WORD_IN_DOUBLE_QOUTE");
	else
		return ("WORD");
}

void	print_t_token_list(t_token_list *head)
{
	t_token_list	*temp;

	temp = head;
	while (temp)
	{
		printf("Token_type: %s Token: %s\n", print_type(temp->token_type),
			temp->token);
		temp = temp->next;
	}
}
