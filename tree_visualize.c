/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_visualize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:30:30 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 20:54:47 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int		g_interrupt_state = 0;

void	signal_handle_parent_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

t_bool	heredoc_check(t_token_all *all)
{
	t_token_list	*tmp;

	tmp = all->head->next;
	while (tmp)
	{
		if (tmp->error_flag == SIGINT)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	wait_pid_list(t_pid_list *pid_list, int *sta)
{
	t_pid_list	*tmp;

	tmp = pid_list->next;
	while (tmp)
	{
		waitpid(tmp->pid, sta, 0);
		tmp = tmp->next;
	}
	if (WIFSIGNALED(*sta))
		*sta = WTERMSIG(*sta) + 128;
	else
		*sta = WEXITSTATUS(*sta);
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

char	*read_and_validate_input(t_minishell *my_shell)
{
	char	*input;

	input = readline("minishell> ");
	if (!input)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		free_all(my_shell);
		exit(0);
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
	if (lexer(input, my_shell->all) == ERROR)
	{
		printf("Close quote\n");
		free_one_loop_data(my_shell);
		return (0);
	}
	expand_heredoc(my_shell->all);
	if (!heredoc_check(my_shell->all))
	{
		free_one_loop_data(my_shell);
		return (0);
	}
	return (1);
}

// ヘルパー3：AST構築・構文チェック・展開・実行
void	run_execution_pipeline(t_minishell *sh)
{
	sh->ast = piped_commands(sh->all);
	if (!syntax_check(sh->all, sh->ast))
		return ;
	expand_env(sh->ast, sh->env->next);
	ft_executer(sh->ast, sh->env->next, sh->parent_fd, sh->pid_list);
	wait_pid_list(sh->pid_list, &sh->state);
	printf("exit state = %d\n", sh->state);
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
		run_execution_pipeline(my_shell);
		free(input);
	}
	return (0);
}
