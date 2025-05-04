/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:31 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 19:49:24 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "../expander/expander.h"
# include <fcntl.h>
# include <sys/types.h> // pid_t などの型定義
# include <sys/wait.h>
# include <unistd.h>
# define TREE_END 1
# define READ_FD 0
# define WRITE_FD 1
# define NO_FILE -1
typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;

}						t_pid_list;

int						ft_executer(t_tree *ast, t_env_list *env,
							int parent_fd[2]);
#endif