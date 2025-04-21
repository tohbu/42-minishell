
#include "./lexer/lexer.h"
#include "./parser/parse.h"
#include <string.h>

void print_token_list(token_list *head) {
    token_list *temp = head;
    while (temp) {
        printf("Token_type: %d Token: %s\n",temp->token_type,temp->token);
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

int main(int argc, char *argv[]) {
    // 入力を格納するためのバッファ
    char input[1024];
	argc++;
	argc--;
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
		//print_ast(ast);
		syntax_check(all,ast);
	}
}