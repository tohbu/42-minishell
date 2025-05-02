#include "./executer/executer.h"
#include "./expander/expander.h"
#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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

int	main(int argc, char *argv[], char *envp[])
{
	// 入力を格納するためのバッファ
	char *input;
	argc++;
	argc--;
	argv++;
	t_env_list *env = get_envp_to_struct(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (strlen(input) > 0)
		{
			add_history(input);
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		t_token_all *all = (t_token_all *)malloc(sizeof(t_token_all));
		if (!all)
			return (1);
		init_t_token_all(all);
		if (lexer(input, all) == ERROR)
		{
			printf("Error in lexer\n");
			return (1);
		}
		print_t_token_list(all->head->next);
		// parse;
		t_tree *ast = piped_commands(all);
		printf("\n");
		expand_env(ast, env->next);
		if (!syntax_check(all, ast))
			continue ;
		t_tree_visualize(ast, 0);
		printf("\n");
		int p_fd[2];
		p_fd[0] = NO_FILE;
		p_fd[1] = NO_FILE;
		ft_executer(ast, env->next, p_fd);
		while (wait(NULL) > 0)
			;
		free_all(all, ast);
		free(input);
	}
}