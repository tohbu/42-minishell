/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:25 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/09 11:57:16 by tomoki-kouk      ###   ########.fr       */
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

void	do_command(char **path, char **argv)
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
	exit(COMAND_NOT_FOUND);
	return ;
}

void	setting_fd(t_command_list *com, t_env_list *env)
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
	close_all_fd();
	do_command(get_path(env), ft_argv);
}

int	exeve_command(t_command_list *com, t_env_list *env, int fd[2],
		t_pid_list *pid_list)
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
		setting_fd(com, env);
		return (1);
	}
	else
	{
		new_pid_node(pid_list, pid);
		return (1);
	}
}

int	ft_executer(t_tree *ast, t_env_list *env, int parent_fd[2],
		t_pid_list *pid_list)
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
		ft_executer(ast->left, env, fds, pid_list);
		close(pipes[WRITE_FD]);
		set_right_fd(parent_fd, pipes, fds);
		ft_executer(ast->right, env, fds, pid_list);
		close(pipes[READ_FD]);
	}
	else
	{
		// if (is_built_in(ast->head->next))
		exeve_command(ast->head->next, env->next, parent_fd, pid_list);
	}
	return (1);
}

int	ft_executer_and_or(t_tree *ast, t_env_list *env, int parent_fd[2],
		t_pid_list *pid_list)
{
	int	sta;

	if (!ast)
		return (TREE_END);
	if (ast->token_type == AND || ast->token_type == OR)
	{
		ft_executer_and_or(ast->left, env, parent_fd, pid_list);
		wait_pid_list(pid_list, &sta);
		printf("sta = %d\n",sta);
		if(sta == 130)
			return sta;
		if ((ast->token_type == AND && sta == 0) || (ast->token_type == OR
			&& sta != 0))
		{
			parent_fd[WRITE_FD] = NO_FILE;
			parent_fd[READ_FD] = NO_FILE;
			ft_executer_and_or(ast->right, env, parent_fd, pid_list);
		}
		else
			return (sta);
	}
	else 
	{
		expand_env(ast, env);
		if(ast->token_type == PIPE)
			ft_executer(ast, env, parent_fd, pid_list);
		else
			exeve_command(ast->head->next,env->next,parent_fd,pid_list);
	}
	return (1);
}
