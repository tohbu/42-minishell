#include "./executer/executer.h"
#include "./expander/expander.h"
#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int		g_interrupt_state = 0;

void	print_tab(int n)
{
	while (n-- > 0)
		printf("     ");
}

void	print_token(int t, t_command_list *head)
{
	t_command_list	*tmp;

	tmp = head->next;
	if (t == PIPE)
		printf("(PIPE)");
	else
		printf("COMMAND");
	while (tmp)
	{
		printf("[%s]", tmp->s);
		tmp = tmp->next;
	}
}

void	t_tree_visualize(t_tree *t, int deep)
{
	if (!t)
		return ;
	print_token(t->token_type, t->head);
	if (t->right)
		printf("--↓--");
	t_tree_visualize(t->right, deep + 1);
	printf("\n");
	print_tab(deep + 1);
	t_tree_visualize(t->left, deep + 1);
}

#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <string.h>

char	*print_type(int token_type)
{
	if (token_type == PIPE)
		return ("PIPE");
	else if (token_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (token_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (token_type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (token_type == HEARDOC)
		return ("HEARDOC");
	else if (token_type == WORD_IN_SINGLE_QOUTE)
		return ("WORD_IN_SINGLE_QOUTE");
	else if (token_type == WORD_IN_DOUBLE_QOUTE)
		return ("WORD_IN_DOUBLE_QOUTE");
	else
		return ("WORD");
}

void	print_t_token_list(t_token_list *head)
{
	t_token_list	*temp;

	temp = head;
	while (temp)
	{
		printf("Token_type: %s Token: %s\n", print_type(temp->token_type),
			temp->token);
		temp = temp->next;
	}
}

void	print_t_command_list(t_command_list *com)
{
	int				i;
	t_command_list	*tmp;

	i = 0;
	if (!com)
	{
		printf("com = NULL\n");
		return ;
	}
	tmp = com;
	while (tmp)
	{
		printf("%d:%s	", i++, tmp->s);
		tmp = tmp->next;
	}
}
void	print_ast(t_tree *t)
{
	if (!t)
		return ;
	print_ast(t->left);
	print_ast(t->right);
	print_t_command_list(t->head->next);
	printf("\n");
}

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
		if (tmp->syntax_error == SIGINT)
		{
			free_all(all, NULL);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_pid_list(t_pid_list *pid_list)
{
	t_pid_list	*tmp;
	int			i;

	i = 0;
	tmp = pid_list->next;
	while (tmp)
	{
		printf("pid[%d] = %d\n", i, tmp->pid);
		tmp = tmp->next;
	}
	return ;
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

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_env_list	*env;
	t_token_all	*all;
	t_tree		*ast;
	t_pid_list	*pid_list;
	int			p_fd[2];
	int			state;

	// 入力を格納するためのバッファ
	argc++;
	argc--;
	argv++;
	env = get_envp_to_struct(envp);
	while (1)
	{
		g_interrupt_state = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handle_parent_c);
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			return (0);
		}
		if (*input)
			add_history(input);
		if (*input == '\0'  )
		{
			free(input);
			continue ;
		}
		all = (t_token_all *)malloc(sizeof(t_token_all));
		if (!all)
			return (1);
		init_t_token_all(all);
		if (lexer(input, all) == ERROR)
		{
			printf("Error in lexer\n");
			return (1);
		}
		expand_heredoc(all);
		if (!heredoc_check(all))
			continue ;
		ast = piped_commands(all);
		if (!syntax_check(all, ast))
			continue ;
		expand_env(ast, env->next);
		t_tree_visualize(ast, 0);
		printf("\n");
		p_fd[0] = NO_FILE;
		p_fd[1] = NO_FILE;
		pid_list = init_pid_list();
		ft_executer(ast, env->next, p_fd, pid_list);
		print_pid_list(pid_list);
		wait_pid_list(pid_list, &state);
		printf("exit state = %d\n", state);
		free_all(all, ast);
		free(input);
	}
}
