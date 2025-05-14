/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:25 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 18:33:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

void	do_command(char **path, char **argv, t_minishell *my_shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, NULL);
	i = 0;
	while (path && path[i])
	{
		tmp = join_path(path[i], argv[0]);
		if (!tmp)
			return ;
		free(path[i]);
		path[i] = tmp;
		execve(path[i], argv, NULL);
		i++;
	}
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	free_char_arr(path);
	free_char_arr(argv);
	free_all(my_shell);
	exit(COMAND_NOT_FOUND);
	return ;
}

void	setting_fd(t_command_list *com, t_minishell *my_shell,
		int paret_token_type)
{
	t_command_list	*tmp;
	char			**ft_argv;
	int				i;

	tmp = com;
	ft_argv = NULL;
	i = 1;
	while (tmp)
	{
		if (REDIRECT_IN <= tmp->token_type && tmp->token_type <= HEARDOC)
		{
			set_redirect(tmp->next->s, tmp->token_type);
			tmp = tmp->next;
		}
		else
			ft_argv = vecter_join(ft_argv, tmp->s, i++);
		tmp = tmp->next;
	}
	if (paret_token_type == PIPE)
		close_all_fd();
	if (is_built_in(com) && paret_token_type == PIPE)
		exit(execute_builtin(ft_argv, my_shell->env->next));
	else if (is_built_in(com))
		my_shell->state = execute_builtin(ft_argv, my_shell->env->next);
	else
		do_command(get_path(my_shell->env->next), ft_argv, my_shell);
}

int	exeve_command(t_command_list *com, int fd[2], t_minishell *my_shell)
{
	pid_t	pid;

	signal(SIGINT, signal_parent_print_newline);
	signal(SIGQUIT, signal_quite_print_message);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), ERROR);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (fd[READ_FD] != NO_FILE)
			dup2(fd[READ_FD], STDIN_FILENO);
		if (fd[WRITE_FD] != NO_FILE)
			dup2(fd[WRITE_FD], STDOUT_FILENO);
		setting_fd(com, my_shell, PIPE);
		return (1);
	}
	else
	{
		new_pid_node(my_shell->pid_list, pid);
		return (1);
	}
}

int	ft_executer(t_tree *ast, int parent_fd[2], t_minishell *my_shell)
{
	int	pipes[2];
	int	fds[2];

	if (!ast)
		return (TREE_END);
	if (ast->token_type == PIPE)
	{
		if (pipe(pipes) < 0)
		{
			perror("pipe");
			return (ERROR);
		}
		set_left_fd(pipes, fds);
		ft_executer(ast->left, fds, my_shell);
		close(pipes[WRITE_FD]);
		set_right_fd(parent_fd, pipes, fds);
		ft_executer(ast->right, fds, my_shell);
		close(pipes[READ_FD]);
	}
	else
		exeve_command(ast->head->next, parent_fd, my_shell);
	return (1);
}

int	ft_executer_and_or(t_tree *ast, t_minishell *my_shell)
{
	if (!ast)
		return (TREE_END);
	if (ast->token_type == AND || ast->token_type == OR)
	{
		ft_executer_and_or(ast->left, my_shell);
		wait_pid_list(my_shell->pid_list, &my_shell->state);
		if (my_shell->state == 130)
			return (my_shell->state);
		if ((ast->token_type == AND && my_shell->state == 0)
			|| (ast->token_type == OR && my_shell->state != 0))
		{
			my_shell->parent_fd[WRITE_FD] = NO_FILE;
			my_shell->parent_fd[READ_FD] = NO_FILE;
			ft_executer_and_or(ast->right, my_shell);
		}
		else
			return (my_shell->state);
	}
	else
	{
		expand_env(ast, my_shell);
		if (ast->token_type == PIPE)
			ft_executer(ast, my_shell->parent_fd, my_shell);
		else if (is_built_in(ast->head->next))
		{
			my_shell->parent_fd[READ_FD] = dup(STDIN_FILENO);
			my_shell->parent_fd[WRITE_FD] = dup(STDOUT_FILENO);
			setting_fd(ast->head->next, my_shell, 0);
			dup2(my_shell->parent_fd[READ_FD], STDIN_FILENO);
			dup2(my_shell->parent_fd[WRITE_FD], STDOUT_FILENO);
			close(my_shell->parent_fd[READ_FD]);
			close(my_shell->parent_fd[WRITE_FD]);
			my_shell->parent_fd[WRITE_FD] = NO_FILE;
			my_shell->parent_fd[READ_FD] = NO_FILE;
		}
		else
			exeve_command(ast->head->next, my_shell->parent_fd, my_shell);
	}
	return (1);
}
