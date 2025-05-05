/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:55:28 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 19:25:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect(t_token_all *all, t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com;
	if (!all || !all->cur || !all->cur->token)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_t_command_list(all->cur->token, all->cur->token_type);
	if (!all->cur->next || !is_token_word(all->cur->next))
		all->cur->error_flag = SYNTAX_ERROR;
}

void	string(t_token_all *all, t_command_list *com)
{
	t_command_list	*tmp;

	if (!com)
		return ;
	tmp = com;
	if (!all || !all->cur || !all->cur->token)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_t_command_list(all->cur->token, all->cur->token_type);
}

t_tree	*command(t_token_all *all)
{
	t_tree	*new;
	int		i;

	i = 0;
	if (!all || !all->cur)
		return (set_syntax_error(all), NULL);
	new = init_node();
	if (!new)
		return (NULL);
	while (all->cur && all->cur->token_type != PIPE)
	{
		if (REDIRECT_IN <= all->cur->token_type
			&& all->cur->token_type <= HEARDOC)
			redirect(all, new->com);
		else
			string(all, new->com);
		all->cur = all->cur->next;
		i++;
	}
	if (i == 0 && all->cur)
		all->cur->error_flag = 1;
	return (new);
}

t_tree	*piped_commands(t_token_all *all)
{
	t_tree	*pipe_right;
	t_tree	*parent;

	if (!all)
		return (NULL);
	parent = command(all);
	while (1)
	{
		if (all && all->cur && all->cur->token_type == PIPE)
		{
			all->cur = all->cur->next;
			pipe_right = command(all);
			parent = new_node(parent, pipe_right, PIPE, "|");
		}
		else
			return (parent);
	}
}
