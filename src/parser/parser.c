/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:55:28 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:13:29 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (token->cur && !(PIPE <= token->cur->token_type
			&& token->cur->token_type <= OR))
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

t_tree	*parser_logical_operator(t_token_manager *token)
{
	t_tree	*tree_right;
	t_tree	*parent;
	int		token_type_tmp;
	char	*token_tmp;

	if (!token)
		return (NULL);
	parent = piped_commands(token);
	while (1)
	{
		if (token && token->cur && (token->cur->token_type == AND
				|| token->cur->token_type == OR))
		{
			token_type_tmp = token->cur->token_type;
			token_tmp = ft_strdup(token->cur->token);
			token->cur = token->cur->next;
			tree_right = piped_commands(token);
			parent = new_node(parent, tree_right, token_type_tmp, token_tmp);
			free(token_tmp);
		}
		else
			return (parent);
	}
}
