/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:25 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:26:07 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_pipeline_tree(t_tree *ast, int parent_fd[2],
		t_minishell *my_shell)
{
	int	pipes[2];
	int	fds[2];

	if (!ast)
		return ;
	if (ast->token_type == PIPE)
	{
		if (pipe(pipes) < 0)
		{
			perror("pipe");
			return ;
		}
		set_left_fd(pipes, fds);
		execute_pipeline_tree(ast->left, fds, my_shell);
		close(pipes[WRITE_FD]);
		set_right_fd(parent_fd, pipes, fds);
		execute_pipeline_tree(ast->right, fds, my_shell);
		close(pipes[READ_FD]);
	}
	else
		fork_and_exec_command(ast->head->next, parent_fd, my_shell);
	return ;
}

void	handle_logical_operator(t_tree *ast, t_minishell *sh)
{
	execute_logical_operater_tree(ast->left, sh);
	wait_pid_list(sh->pid_list, &sh->state);
	if (sh->state == 130)
		return ;
	if ((ast->token_type == AND && sh->state == 0) || (ast->token_type == OR
			&& sh->state != 0))
	{
		sh->parent_fd[WRITE_FD] = NO_FILE;
		sh->parent_fd[READ_FD] = NO_FILE;
		execute_logical_operater_tree(ast->right, sh);
	}
	return ;
}

void	execute_single_command(t_tree *ast, t_minishell *sh)
{
	expand_env(ast, sh);
	if (ast->token_type == PIPE)
		execute_pipeline_tree(ast, sh->parent_fd, sh);
	else if (is_built_in(ast->head->next))
	{
		sh->parent_fd[READ_FD] = dup(STDIN_FILENO);
		sh->parent_fd[WRITE_FD] = dup(STDOUT_FILENO);
		handle_redirect_and_argv(ast->head->next, sh, 0);
		dup2(sh->parent_fd[READ_FD], STDIN_FILENO);
		dup2(sh->parent_fd[WRITE_FD], STDOUT_FILENO);
		close(sh->parent_fd[READ_FD]);
		close(sh->parent_fd[WRITE_FD]);
		sh->parent_fd[WRITE_FD] = NO_FILE;
		sh->parent_fd[READ_FD] = NO_FILE;
	}
	else
		fork_and_exec_command(ast->head->next, sh->parent_fd, sh);
}

void	execute_logical_operater_tree(t_tree *ast, t_minishell *sh)
{
	if (!ast)
		return ;
	if (ast->token_type == AND || ast->token_type == OR)
		handle_logical_operator(ast, sh);
	else
		execute_single_command(ast, sh);
	return ;
}
