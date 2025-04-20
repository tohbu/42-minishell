#include "parse.h"

command_list	*new_command_list(char *s)
{
	command_list	*new;

	new = (command_list *)malloc(sizeof(command_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->s = ft_strdup(s);
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

tree	*new_node(tree *l, tree *r, int t_type, char *s)
{
	tree	*new;

	new = (tree *)malloc(sizeof(tree));
	if (!new)
		return (NULL);
	new->token_type = t_type;
	new->left = l;
	new->right = r;
	new->com = new_command_list(ft_strdup(s));
	new->head = new->com;
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

tree	*piped_commands(token_all *all)
{
	tree	*new;

	if (!all)
		return (NULL);
	new = command(all);
	while (1)
	{
		if (token_type_check_and_next(all) == PIPE)
			new = new_node(new, piped_commands(all), PIPE, "|");
		else
			return (new);
	}
}

tree	*command(token_all *all)
{
	tree	*new;

	if (!all || !all->cur)
		return (NULL);
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
			new->com = redirect(all);
		else
			new->com = string(all);
		new->com = new->com->next;
		all->cur = all->cur->next;
	}
	return (new);
}

command_list	*redirect(token_all *all)
{
	command_list	*result;

	if (!all || !all->cur || !all->cur->token)
		return (NULL);
	result = new_command_list(all->cur->token);
	if (!result)
		return (NULL);
	if (!all->cur->next || !is_token_word(all->cur->next))
		all->cur->syntax_error = SYNTAX_ERROR;
	return (result);
}

command_list	*string(token_all *all)
{
	command_list	*result;

	if (!all || !all->cur || !all->cur->token)
		return (NULL);
	result = new_command_list(all->cur->token);
	if (!result)
		return (NULL);
	return (result);
}

// t->com = t->com->next;
// all->cur = all->cur->next;
// while (all->cur && is_token_word(all->cur))
// {
// 	t->com->next = new_command_list(all->cur->token);
// 	if (t->com->next)
// 		return (NULL);
// 	t->com = t->com->next;
// 	all->cur = all->cur->next;
// }
// return (t);
