/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:14:37 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:13:29 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_command_list(t_command_list *com)
{
	if (!com)
		return ;
	free_t_command_list(com->next);
	free(com->s);
	free(com);
}

void	free_t_tree(t_tree *t)
{
	if (t == NULL)
		return ;
	free_t_tree(t->left);
	free_t_tree(t->right);
	free_t_command_list(t->head);
	free(t);
}

void	free_t_token_list(t_token_list *tok)
{
	if (!tok)
		return ;
	free_t_token_list(tok->next);
	free(tok->token);
	free(tok);
}

void	free_t_token_manager(t_token_manager *token)
{
	if (!token)
		return ;
	free_t_token_list(token->head);
	free(token);
}

void	free_pid_list(t_pid_list *pid)
{
	if (!pid)
		return ;
	free_pid_list(pid->next);
	free(pid);
}
