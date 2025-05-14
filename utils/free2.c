/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:57:43 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:47:26 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_one_loop_data(t_minishell *myshell)
{
	free_t_tree(myshell->ast);
	free_t_token_manager(myshell->token);
	free_pid_list(myshell->pid_list);
	myshell->ast = NULL;
	myshell->token = NULL;
	myshell->pid_list = NULL;
}

void	free_envlist(t_env_list *t)
{
	if (!t)
		return ;
	free_envlist(t->next);
	free(t->key);
	free(t->value);
	free(t);
}

void	free_all(t_minishell *my_shell)
{
	free_one_loop_data(my_shell);
	free_envlist(my_shell->env);
	free(my_shell);
}

void	free_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
}
