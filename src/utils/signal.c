/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:17:32 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:13:29 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle_print_readline(int sig)
{
	g_interrupt_state = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_parent_print_newline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	signal_quite_print_message(int sig)
{
	(void)(sig);
	write(2, "Quit (core dumped)\n", 20);
}

void	signal_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_interrupt_state = SIGINT;
}

void	set_up_signal_heredoc(void)
{
	struct sigaction	sig;

	sig.sa_handler = signal_heredoc;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
}
