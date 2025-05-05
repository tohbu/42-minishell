/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:57:59 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 22:54:56 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*init_minishell(char *envp[])
{
	t_minishell	*my_shell;

	my_shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!my_shell)
		return (NULL);
	my_shell->token = init_t_token_manager();
	my_shell->pid_list = init_pid_list();
	my_shell->env = get_envp_to_struct(envp);
	my_shell->ast = NULL;
	my_shell->parent_fd[0] = NO_FILE;
	my_shell->parent_fd[1] = NO_FILE;
	my_shell->state = 0;
	return (my_shell);
}

t_minishell	*setup_data(t_minishell *minishell)
{
	if (minishell->token == NULL)
		minishell->token = init_t_token_manager();
	if (minishell->pid_list == NULL)
		minishell->pid_list = init_pid_list();
	g_interrupt_state = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handle_print_readline);
	return (minishell);
}

t_bool	check_input_only_space(char *s)
{
	while (*s)
	{
		if (!check_space(*s))
			return (0);
		s++;
	}
	return (1);
}
