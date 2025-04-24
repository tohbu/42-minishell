#ifndef PARSE_H
#define PARSE_H 
#include "../lexer/lexer.h"

#define SYNTAX_ERROR 1

typedef struct word
{
	char				*s;
	int					token_type;
}						word;

typedef struct command_list
{
	struct command_list	*next;
	char				*s;

}						command_list;

typedef struct node
{
	struct node			*left;
	struct node			*right;
	int					token_type;
	command_list		*com;
	command_list		*head;
}						tree;

void p_command_list(command_list *com);
int	token_type_check_and_next(token_all *all);
tree	*new_node(tree *l, tree *r, int t_type, char *s);
t_bool	is_token_word(token_list *t);
command_list	*new_command_list(char *s);
t_bool syntax_check(token_all *all,tree*t);

void 	redirect(token_all *all,command_list *com);
void	string(token_all *all, command_list *com);
tree	*command(token_all *all);
tree	*piped_commands(token_all *all);

void free_command_list(command_list *com);
void free_tree(tree* t);
void free_token_list(token_list* tok);
void free_token_all(token_all* all);
void free_all(token_all *all, tree*t);




#endif
