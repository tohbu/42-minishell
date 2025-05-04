/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:31 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 21:49:12 by tohbu            ###   ########.fr       */
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
# define COMAND_NOT_FOUND 127
typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;

}						t_pid_list;

int						exeve_command(t_command_list *com, t_env_list *env,
							int fd[2], t_pid_list *pid_list);
int						ft_executer(t_tree *ast, t_env_list *env,
							int parent_fd[2], t_pid_list *pid_list);
t_pid_list				*init_pid_list(void);
t_pid_list				*new_pid_node(t_pid_list *head, pid_t p_id);

#endif