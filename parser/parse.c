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
	new->s = str;
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

t_bool syntax_check(token_all *all)
{
	token_list* tmp;
	tmp = all->head->next;
	while(tmp)
	{
		if(tmp->syntax_error == SYNTAX_ERROR)
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n",tmp->token);
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

void 	redirect(token_all *all,command_list *com)
{
	command_list	*tmp;
	tmp = com;

	if (!all || !all->cur || !all->cur->token)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_command_list(all->cur->token);
	if (!all->cur->next || !is_token_word(all->cur->next))
		all->cur->syntax_error = SYNTAX_ERROR;
}

	void	string(token_all *all, command_list *com)
	{
		command_list	*tmp;
		
		tmp = com;
		if (!all || !all->cur || !all->cur->token)
			return;
		// printf("string %s\n", all->cur->token);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_command_list(all->cur->token);

	}
		
	tree	*command(token_all *all)
	{
		tree	*new;
		int i = 0;
	
		if (!all || !all->cur)
		{
			token_list *tmp = all->head->next;
			while (tmp->next)
				tmp = tmp->next;
			tmp->syntax_error = 1;
			return (NULL);
		}
		new = (tree *)malloc(sizeof(tree));
		if (!new)
			return (NULL);
		new->head = (command_list *)malloc(sizeof(command_list));
		if (!new)
			return (NULL);
		new->com = new->head;
		while (all->cur != NULL && all->cur->token_type != PIPE)
		{
			if (all->cur->token_type == REDIRECT || all->cur->token_type == HEARDOC)
				redirect(all,new->com);
			else
				string(all,new->com);
			all->cur = all->cur->next;
			i++;
		}
		if(i == 0)
			all->cur->syntax_error = 1;
		return (new);
	}

	tree	*piped_commands(token_all *all)
	{
		tree 	*pipe_right;
		tree	*parent;

		if (!all)
			return (NULL);
		parent = command(all);
		while (1)
		{
			if (token_type_check_and_next(all) == PIPE)
			{
				pipe_right = command(all);
				parent = new_node(parent,pipe_right, PIPE, "|");
			}
			else
				return (parent);
		}
	}



