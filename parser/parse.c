#include "parse.h"



tree* new_node(tree* l, tree*r, int t_type, char *s)
{
	tree* new = (tree*)malloc(sizeof(tree));
		if(!new)
			return NULL;
	new->token_type =t_type;
	new->left = l;
	new->right = r;
	new->s = ft_strdup(s);
	return new;
}


tree* piped_commands(token_all *all, tree* t)
{
	if(all->pipe_n > 0)
	{
		command(all,t->left);
		piped_commands(all,t->right);
	}
	else
	{
		command(all,t);
	}
}


void command(token_all *all,tree* t)
{


}

void argumetes(token_all *all,tree* t)
{

}


void redirect(token_all *all,tree* t)
{

}

void strinf(token_all *all,tree *t)
{

}