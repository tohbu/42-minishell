#include <stdio.h>
#include <stdlib.h>
#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include "./expander/executer.h"

void print_tab(int n)
{
	while (n-- > 0)
		printf("     ");
}

void print_token(int t, command_list *head)
{
	command_list* tmp = head->next;
	if(t == PIPE)
		printf("(PIPE)");
	else 
		printf("COMMAND");
	while (tmp)
	{
		printf("[%s]",tmp->s);
		tmp = tmp->next;
	}
	
}


void tree_visualize(tree *t, int deep)
{
	if(!t)
		return;
	print_token(t->token_type,t->head);
	if(t->right)
		printf("--↓--");
	tree_visualize(t->right,deep+1);
	printf("\n");
	print_tab(deep+1);
	tree_visualize(t->left,deep+1);
}



#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <string.h>

char * print_type(int token_type)
{
    if (token_type == PIPE)
        return "PIPE";
    else if (token_type == REDIRECT)
        return "REDIRECT";
    else if (token_type == HEARDOC)
        return "HEARDOC";
    else if (token_type == WORD_IN_SINGLE_QOUTE)
        return "WORD_IN_SINGLE_QOUTE";
    else if (token_type == WORD_IN_DOUBLE_QOUTE)
        return "WORD_IN_DOUBLE_QOUTE";
    else if (token_type == FILENAME)
        return "FILENAME";
    else if (token_type == LIMITER)
        return "LIMITER";
    else 
        return "WORD";
}


void print_token_list(token_list *head) {
    token_list *temp = head;
    while (temp) {
        printf("Token_type: %s Token: %s\n",print_type(temp->token_type),temp->token);
        temp = temp->next;
    }
}

void print_command_list(command_list *com)
{
	int i = 0;
	if(!com)
	{
		printf("com = NULL\n");
		return;
	}
	command_list* tmp = com;
	while(tmp)
	{
		printf("%d:%s	",i++,tmp->s);
		tmp = tmp->next;
	}	
}

void print_ast(tree *t)
{
	if(!t)
		return;
	print_ast(t->left);
	print_ast(t->right);
	print_command_list(t->head->next);
	printf("\n");
}

int main(int argc, char *argv[],char *envp[]) {
    // 入力を格納するためのバッファ
    char input[1024];
	argc++;
	argc--;
	t_env_list *env = get_envp_to_struct(envp);
	while (1)
	{
		printf("%s> ",argv[0]);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("Error reading input.\n");
			return 1;
		}
		input[strcspn(input, "\n")] = 0;
		token_all *all = (token_all*)malloc(sizeof(token_all));
		if(!all)
			return 1;
		init_token_all(all);
		if (lexer(input, all) == ERROR) {
			printf("Error in lexer\n");
			return 1;
		}
		print_token_list(all->head->next);
		//parse;
		tree* ast = piped_commands(all);
		tree_visualize(ast,0);
		printf("\n");
		syntax_check(all,ast);
		expand_env(ast,env->next);
		tree_visualize(ast,0);

	}
}