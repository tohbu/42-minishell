/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:34:25 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 21:25:07 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_t_token_list(t_token_list *head)
{
	t_token_list	*temp;

	temp = head;
	while (temp)
	{
		printf("Token_type: %d Token: %s\n", temp->token_type, temp->token);
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
	char			*input;
	t_token_manager	*all;
	t_tree			*ast;

	argc++;
	argc--;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (strlen(input) > 0)
		{
			add_history(input); /* 履歴を保存 */
		}
		// all = (t_token_manager *)malloc(sizeof(t_token_manager));
		// if (!all)
		// 	return (1);
		all = init_t_token_manager();
		// init_t_token_manager(all);
		if (lexer(input, all) == ERROR)
		{
			printf("Error in lexer\n");
			return (1);
		}
		print_t_token_list(all->head->next);
		// parse;
		ast = piped_commands(all);
		// print_ast(ast);
		syntax_check(all, ast);
		free(input);
	}
}
