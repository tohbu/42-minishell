/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:38:53 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 23:14:36 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"
# include "struct.h"
// free1.c
void		free_t_command_list(t_command_list *com);
void		free_t_tree(t_tree *t);
void		free_t_token_list(t_token_list *tok);
void		free_t_token_manager(t_token_manager *token);
void		free_pid_list(t_pid_list *pid);
// free2.c
void		free_one_loop_data(t_minishell *myshell);
void		free_all(t_minishell *my_shell);
void		free_envlist(t_env_list *t);

// print1.c
void		print_tab(int n);
void		print_token(int t, t_command_list *head);
void		t_tree_visualize(t_tree *t, int deep);
char		*print_type(int token_type);
void		print_t_token_list(t_token_list *head);
// print2.c
void		print_t_command_list(t_command_list *com);
void		print_pid_list(t_pid_list *pid_list);
void		print_env_list(t_env_list *t);
void		print_debag(t_minishell *my_shell);
// init_minishell.c
t_minishell	*init_minishell(char *envp[]);
t_minishell	*setup_data(t_minishell *minishell);
t_bool		check_input_only_space(char *s);
// signal.c
void		signal_handle_print_readline(int sig);
void		signal_parent_print_newline(int sig);
void		signal_quite_print_message(int sig);
void		signal_heredoc(int sig);
void		set_up_signal_heredoc(void);

#endif
