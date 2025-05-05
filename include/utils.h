/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:38:53 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 20:51:14 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"
# include "struct.h"
// free.c
void		free_t_command_list(t_command_list *com);
void		free_t_tree(t_tree *t);
void		free_t_token_list(t_token_list *tok);
void		free_t_token_all(t_token_all *all);
void		free_one_loop_data(t_minishell *myshell);
void		free_all(t_minishell *my_shell);
// print.c
void		print_tab(int n);
void		print_token(int t, t_command_list *head);
void		t_tree_visualize(t_tree *t, int deep);
char		*print_type(int token_type);
void		print_t_token_list(t_token_list *head);
void		print_t_command_list(t_command_list *com);
void		print_ast(t_tree *t);
void		print_pid_list(t_pid_list *pid_list);
void		print_env_list(t_env_list *t);
// init_minishell.c
t_minishell	*init_minishell(char *envp[]);
t_minishell	*setup_data(t_minishell *minishell);
#endif
