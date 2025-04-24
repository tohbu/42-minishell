
#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <string.h>

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
	char input[1024];
	argc++;
	argc--;
	while (1)
	{
		printf("%s> ", argv[0]);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("Error reading input.\n");
			return (1);
		}
		input[strcspn(input, "\n")] = 0;
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
		// print_ast(ast);
		syntax_check(all, ast);
	}
}