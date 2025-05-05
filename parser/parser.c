/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:55:28 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 21:57:14 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_token_word(t_token_list *t)
{
	if (t->token_type == WORD || t->token_type == WORD_IN_DOUBLE_QOUTE
		|| t->token_type == WORD_IN_SINGLE_QOUTE)
		return (1);
	else
		return (0);
}

void	redirect(t_token_manager *token, t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com;
	if (!token || !token->cur || !token->cur->token)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_t_command_list(token->cur->token, token->cur->token_type);
	if (!token->cur->next || !is_token_word(token->cur->next))
		token->cur->error_flag = SYNTAX_ERROR;
}

void	string(t_token_manager *token, t_command_list *com)
{
	t_command_list	*tmp;

	if (!com)
		return ;
	tmp = com;
	if (!token || !token->cur || !token->cur->token)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_t_command_list(token->cur->token, token->cur->token_type);
}

t_tree	*command(t_token_manager *token)
{
	t_tree	*new;
	int		i;

	i = 0;
	if (!token || !token->cur)
		return (set_syntax_error(token), NULL);
	new = init_node();
	if (!new)
		return (NULL);
	while (token->cur && token->cur->token_type != PIPE)
	{
		if (REDIRECT_IN <= token->cur->token_type
			&& token->cur->token_type <= HEARDOC)
			redirect(token, new->com);
		else
			string(token, new->com);
		token->cur = token->cur->next;
		i++;
	}
	if (i == 0 && token->cur)
		token->cur->error_flag = SYNTAX_ERROR;
	return (new);
}

t_tree	*piped_commands(t_token_manager *token)
{
	t_tree	*pipe_right;
	t_tree	*parent;

	if (!token)
		return (NULL);
	parent = command(token);
	while (1)
	{
		if (token && token->cur && token->cur->token_type == PIPE)
		{
			token->cur = token->cur->next;
			pipe_right = command(token);
			parent = new_node(parent, pipe_right, PIPE, "|");
		}
		else
			return (parent);
	}
}
