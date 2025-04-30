/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:31 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/29 18:01:37 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "../expander/expander.h"
# include <fcntl.h>
# include <unistd.h>
# define TREE_END 1
# define READ_FD 0
# define WRITE_FD 1
# define NO_FILE -1
int	ft_executer(t_tree *ast, t_env_list *env, int parent_fd[2]);
#endif