/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:31 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 19:22:43 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "minishell.h"
# include "struct.h"

int			exeve_command(t_command_list *com, t_env_list *env, int fd[2],
				t_pid_list *pid_list);
int			ft_executer(t_tree *ast, t_env_list *env, int parent_fd[2],
				t_pid_list *pid_list);
t_pid_list	*init_pid_list(void);
t_pid_list	*new_pid_node(t_pid_list *head, pid_t p_id);

#endif