/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:35:14 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 22:50:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		exit(1);
	}
	write(p_fd[WRITE_FD], s, ft_strlen(s));
	dup2(p_fd[READ_FD], STDIN_FILENO);
}

void	set_redirect(char *filename, int token_type)
{
	int		fd;
	char	*error_message;

	if (token_type == HEARDOC)
	{
		set_heardoc(filename);
		return ;
	}
	fd = NO_FILE;
	fd = ft_open(filename, token_type);
	if (fd < 0)
	{
		error_message = ft_strjoin("minishell: ", filename);
		return (perror(error_message), exit(1));
	}
	if (token_type == REDIRECT_IN)
		dup2(fd, STDIN_FILENO);
	else if (token_type == REDIRECT_OUT || token_type == REDIRECT_APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
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
