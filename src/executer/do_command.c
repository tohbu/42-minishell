/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:14:33 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:13:29 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env_list *env)
{
	char		**reslut;
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
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

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

void	try_execve(char **path, char **argv, t_minishell *my_shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (argv == NULL)
		exit(0);
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
	free_char_arr(argv);
	free_all(my_shell);
	exit(COMAND_NOT_FOUND);
	return ;
}

void	handle_redirect_and_argv(t_command_list *com, t_minishell *my_shell,
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
			ft_argv = join_argv(ft_argv, tmp->s, i++);
		tmp = tmp->next;
	}
	if (paret_token_type == PIPE && close_all_fd() && is_built_in(com))
		exit(execute_builtin(ft_argv, my_shell->env->next));
	else if (is_built_in(com))
		my_shell->state = execute_builtin(ft_argv, my_shell->env->next);
	else
		try_execve(get_path(my_shell->env->next), ft_argv, my_shell);
}

int	fork_and_exec_command(t_command_list *com, int fd[2], t_minishell *my_shell)
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
		handle_redirect_and_argv(com, my_shell, PIPE);
	}
	else
		new_pid_node(my_shell->pid_list, pid);
	return (1);
}
