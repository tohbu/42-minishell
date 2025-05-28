/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:30:30 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/28 15:21:45 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_interrupt_state = 0;

char	*read_and_validate_input(t_minishell *my_shell)
{
	char	*input;
	char	*prompt;
	int		state;

	prompt = ft_strjoin_and_free(match_env_key("PWD", my_shell->env->next),
			ft_strdup("$ "));
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		if (g_interrupt_state != 0)
			my_shell->state = g_interrupt_state + 128;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		state = my_shell->state;
		free_all(my_shell);
		exit(state);
	}
	if (*input)
		add_history(input);
	if (*input == '\0' || check_input_only_space(input))
	{
		free(input);
		return (NULL);
	}
	return (input);
}

t_bool	run_lexer_and_heredoc(char *input, t_minishell *my_shell)
{
	if (lexer(input, my_shell->token) == ERROR)
	{
		printf("malloc_error\n");
		free_one_loop_data(my_shell);
		return (0);
	}
	expand_heredoc(my_shell->token, my_shell);
	if (!heredoc_check(my_shell->token))
	{
		free_one_loop_data(my_shell);
		return (0);
	}
	return (1);
}

void	parser_and_executer(t_minishell *sh)
{
	sh->ast = parser_logical_operator(sh->token);
	if (!syntax_check(sh->token, sh->ast))
	{
		sh->state = SYNTAX_ERROR;
		free_one_loop_data(sh);
		return ;
	}
	print_debag(sh);
	execute_logical_operater_tree(sh->ast, sh);
	if (sh->pid_list && sh->pid_list->next)
		wait_pid_list(sh->pid_list, &sh->state);
	free_one_loop_data(sh);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_minishell	*my_shell;

	(void)argc;
	(void)argv;
	my_shell = init_minishell(envp);
	while (1)
	{
		my_shell = setup_data(my_shell);
		input = read_and_validate_input(my_shell);
		if (!input)
			continue ;
		if (!run_lexer_and_heredoc(input, my_shell))
		{
			free(input);
			continue ;
		}
		parser_and_executer(my_shell);
		free(input);
	}
	return (0);
}
