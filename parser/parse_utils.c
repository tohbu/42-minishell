#include "parse.h"

void p_command_list(command_list *com)
{
	int i = 0;
	if(!com)
	{
		return;
	}
	command_list* tmp = com;
	while(tmp != NULL)
	{
		printf("%d:%s	",i++,tmp->s);
		tmp = tmp->next;
	}	
}

command_list	*new_command_list(char *str)
{
	command_list	*new;

	new = (command_list *)malloc(sizeof(command_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->s = ft_strdup(str);
	return (new);
}

t_bool	is_token_word(token_list *t)
{
	if (t->token_type == WORD || t->token_type == WORD_IN_DOUBLE_QOUTE
		|| t->token_type == WORD_IN_SINGLE_QOUTE)
		return (1);
	else
		return (0);
}

t_bool syntax_check(token_all *all,tree* t)
{
	token_list* tmp;
	tmp = all->head->next;
	while(tmp)
	{
		if(tmp->syntax_error == SYNTAX_ERROR)
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n",tmp->token);
			free_all(all,t);
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;

}

tree	*new_node(tree *l, tree *r, int t_type, char *s)
{
	tree	*new;

	new = (tree *)malloc(sizeof(tree));
	if (!new)
	return (NULL);
	new->token_type = t_type;
	new->left = l;
	new->right = r;
	new->head = (command_list*)malloc(sizeof(command_list));
	new->head->next = new_command_list(s);
	new->com = new->head->next;
	return (new);
}

int	token_type_check_and_next(token_all *all)
{
	int	result;
	
	if (!all)
	return (ERROR);
	if (!all->cur)
	return (TOKEN_END);
	result = all->cur->token_type;
	all->cur = all->cur->next;
	return (result);
}