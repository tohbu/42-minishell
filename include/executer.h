/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:31 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 16:19:53 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "minishell.h"
# include "struct.h"

// fd_manage.c
int			ft_open(char *filename, int token_type);
void		set_heardoc(char *s);
void		set_redirect(char *filename, int token_type);
void		set_left_fd(int now_pipe[2], int set_fd[2]);
void		set_right_fd(int parent_fd[2], int now_pipe[2], int set_fd[2]);
// pid_list.c
t_pid_list	*new_pid_node(t_pid_list *head, pid_t p_id);
t_pid_list	*init_pid_list(void);
void		wait_pid_list(t_pid_list *pid_list, int *sta);

// executer_utils.c
void		close_all_fd(void);
t_bool		ft_strcmp_built_in(char *s);
t_bool		is_built_in(t_command_list *com);
char		**vecter_join(char **array, char *s, int size);
char		**get_path(t_env_list *env);
// executer.c
char		*join_path(char *dir, char *cmd);
void		do_command(char **path, char **argv, t_minishell *my_shell);
void		setting_fd(t_command_list *com, t_minishell *my_shell,
				int paret_token_type);
int			exeve_command(t_command_list *com, int fd[2],
				t_minishell *my_shell);
int			ft_executer(t_tree *ast, int parent_fd[2], t_minishell *my_shell);
int			ft_executer_and_or(t_tree *ast, t_minishell *my_shell);
#endif