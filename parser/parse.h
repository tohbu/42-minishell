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
