#include "parse.h"


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
		if(!com)
			return ;
		tmp = com;
		if (!all || !all->cur || !all->cur->token)
			return;
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
		new->left = NULL;
		new->right = NULL;
		new->head = (command_list *)malloc(sizeof(command_list));
		new->head->next = NULL;
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
