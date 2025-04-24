#include "parse.h"
#include "lexer.h"

void free_command_list(command_list *com)
{
	if(!com)
		return;
	free_command_list(com->next);
	free(com->s);
	free(com);
}

void free_tree(tree* t)
{
    if (t == NULL)
        return;
    free_tree(t->left);
    free_tree(t->right);
	free_command_list(t->head);
	free(t);  // 最後にtree自体を解放
}

void free_token_list(token_list* tok)
{
	if(!tok)
		return;
	free_token_list(tok->next);
	free(tok->token);
	free(tok);
}

void free_token_all(token_all* all)
{
	if(!all)
		return;
	free_token_list(all->head);
	free(all);
}
void free_all(token_all *all, tree*t)
{
	free_tree(t);
	free_token_all(all);
}

