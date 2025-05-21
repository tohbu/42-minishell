/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:32:16 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/21 12:13:29 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_manager	*init_t_token_manager(void)
{
	t_token_manager	*token;

	token = (t_token_manager *)malloc(sizeof(t_token_manager));
	token->head = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token->head)
		return (NULL);
	token->cur = token->head;
	token->head->token = NULL;
	token->head->next = NULL;
	token->head->token_type = 0;
	token->head->error_flag = 0;
	return (token);
}

t_token_list	*add_list(char *s)
{
	t_token_list	*new;

	new = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new || !s)
		return (NULL);
	new->token = s;
	if (!new->token)
		return (NULL);
	new->token_type = get_token_type(s);
	new->error_flag = 0;
	new->next = NULL;
	return (new);
}
