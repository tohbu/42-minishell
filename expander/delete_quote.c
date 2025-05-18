/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:46 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/18 20:10:46 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*delete_quote(char *s)
{
	char	*result;

	if (ft_strcmp(s, "\"\"") == 0 || ft_strcmp(s, "\'\'") == 0)
		result = ft_calloc(sizeof(char *), 1);
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}

char	*delete_quote_for_heredoc(char *s)
{
	char	*result;

	if (ft_strcmp(s, "\"\"") == 0 || ft_strcmp(s, "\'\'") == 0)
		result = ft_calloc(sizeof(char *), 1);
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}

char	*handle_single_quote(char *s, t_token_manager *token)
{
	char	*start;

	start = s++;
	while (*s && *s != '\'')
		s++;
	if (!*s)
		return (NULL);
	token->cur->next = add_list(ft_strndup(start, s - start + 1));
	return (s + 1);
}

char	*handle_double_quote(char *s, t_token_manager *token)
{
	char	*start;

	start = s++;
	while (*s && *s != '\"')
		s++;
	if (!*s)
		return (NULL);
	token->cur->next = add_list(ft_strndup(start, s - start + 1));
	return (s + 1);
}

char	*handle_word_for_expander(char *s, t_token_manager *token)
{
	char	*start;

	start = s;
	while (*s && !check_space(*s) && !check_meta_word(*s) && !check_quote(*s))
		s++;
	token->cur->next = add_list(ft_strndup(start, s - start));
	return (s);
}

t_bool	lexer_for_delete_quote(char *one_line, t_token_manager *token)
{
	while (*one_line)
	{
		while (*one_line && check_space(*one_line))
			one_line++;
		if (!*one_line)
			break ;
		if (check_meta_word(*one_line))
			one_line = handle_meta(one_line, token);
		else if (*one_line == '\'')
			one_line = handle_single_quote(one_line, token);
		else if (*one_line == '\"')
			one_line = handle_double_quote(one_line, token);
		else
			one_line = handle_word_for_expander(one_line, token);
		if (!one_line || !token->cur->next)
			return (ERROR);
		token->cur = token->cur->next;
	}
	token->cur = token->head->next;
	return (1);
}

char	*strjoin_token_list(t_token_list *tokne_list)
{
	char			*result;
	char			*pre;
	t_token_list	*tmp;

	tmp = tokne_list;
	result = ft_strdup(tmp->token);
	while (tmp->next)
	{
		pre = result;
		result = ft_strjoin(pre, tmp->next->token);
		free(pre);
		tmp = tmp->next;
	}
	return (result);
}

char	*delete_quote_sub(char *com, t_token_manager *token_mg)
{
	t_token_list	*tmp;
	char			*result;

	lexer_for_delete_quote(com, token_mg);
	tmp = token_mg->head->next;
	while (tmp)
	{
		if (ft_strchr(tmp->token, SINGLE_QUOTE_CHAR) || ft_strchr(tmp->token,
				DOUBLE_QUOTE_CHAR))
			tmp->token = delete_quote(tmp->token);
		tmp = tmp->next;
	}
	result = strjoin_token_list(token_mg->head->next);
	free(com);
	free_t_token_manager(token_mg);
	return (result);
}

void	delete_quote_com(t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com->next;
	while ((tmp))
	{
		if (tmp->token_type == HEARDOC)
			tmp = tmp->next;
		else if (tmp->token_type == WORD)
			tmp->s = delete_quote_sub(tmp->s, init_t_token_manager());
		tmp = tmp->next;
	}
}
