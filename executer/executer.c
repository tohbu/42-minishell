/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:50:25 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 19:43:55 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include <unistd.h>

t_bool	ft_strcmp_built_in(char *s)
{
	if (strcmp(s, "echo") == 0 || strcmp(s, "cd") == 0 || strcmp(s, "pwd") == 0
		|| strcmp(s, "export") == 0)
		return (1);
	if (strcmp(s, "unset") == 0 || strcmp(s, "env") == 0 || strcmp(s,
			"exit") == 0)
		return (1);
	return (0);
}

t_bool	is_built_in(t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com;
	while (tmp)
	{
		if (REDIRECT_IN <= tmp->token_type && tmp->token_type <= HEARDOC)
			tmp = tmp->next;
		else
			return (ft_strcmp_built_in(tmp->s));
		tmp = tmp->next;
	}
	return (0);
}
char	**vecter_join(char **array, char *s, int size)
{
	char	**reslut;
	int		i;

	reslut = (char **)malloc(sizeof(char *) * (size + 1));
	if (!reslut)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		reslut[i] = array[i];
		i++;
	}
	reslut[i++] = ft_strdup(s);
	reslut[i] = NULL;
	if (array)
		free(array);
	return (reslut);
}

int	ft_open(char *filename, int token_type)
{
	int	fd;

	fd = NO_FILE;
	if (token_type == REDIRECT_IN)
		fd = open(filename, O_RDONLY);
	else if (token_type == REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (token_type == REDIRECT_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	set_heardoc(char *s)
{
	int	p_fd[2];

	if (pipe(p_fd) < 0)
	{
		perror("pipe");
		exit(ERROR);
	}
	write(p_fd[WRITE_FD], s, ft_strlen(s));
	dup2(p_fd[READ_FD], STDIN_FILENO);
}

void	set_redirect(char *filename, int token_type)
{
	int	fd;

	if (token_type == HEARDOC)
	{
		set_heardoc(filename);
		return ;
	}
	fd = NO_FILE;
	fd = ft_open(filename, token_type);
	if (fd < 0)
	{
		return (perror("minishell: "), exit(ERROR));
	}
	if (token_type == REDIRECT_IN)
		dup2(fd, STDIN_FILENO);
	else if (token_type == REDIRECT_OUT || token_type == REDIRECT_APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

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
	print_argv(argv);
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
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(ERROR);
	return ;
}

char	**get_path(t_env_list *env)
{
	char		**reslut;
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	reslut = ft_split(tmp->value, ':');
	if (!reslut)
		return (NULL);
	return (reslut);
}

void	close_all_fd(void)
{
	int	i;

	i = STDERR_FILENO + 1;
	while (close(i) != -1)
		i++;
	return ;
}

void	do_process(t_command_list *com, t_env_list *env)
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

void	signal_parent_print_newline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}
void	signal_quite_print_message(int sig)
{
	(void)(sig);
	write(2, "Quit (core dumped)\n", 20);
}
int	exeve_command(t_command_list *com, t_env_list *env, int fd[2])
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
		do_process(com, env);
		return (1);
	}
	else
		return (1);
}

void	set_left_fd(int now_pipe[2], int set_fd[2])
{
	set_fd[READ_FD] = NO_FILE;
	set_fd[WRITE_FD] = now_pipe[WRITE_FD];
}

void	set_right_fd(int parent_fd[2], int now_pipe[2], int set_fd[2])
{
	set_fd[READ_FD] = now_pipe[READ_FD];
	set_fd[WRITE_FD] = parent_fd[WRITE_FD];
}

int	ft_executer(t_tree *ast, t_env_list *env, int parent_fd[2])
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
		ft_executer(ast->left, env, fds);
		close(pipes[WRITE_FD]);
		set_right_fd(parent_fd, pipes, fds);
		ft_executer(ast->right, env, fds);
		close(pipes[READ_FD]);
	}
	else
	{
		// if (is_built_in(ast->head->next))
		// {
		// 	execve_built_in(ast, env, parent_fd);
		// }
		// else
		// {
		exeve_command(ast->head->next, env->next, parent_fd);
		//
	}
	return (1);
}
