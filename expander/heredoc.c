/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:01 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/29 13:48:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*delete_quote_for_heredoc(char *s)
{
	char	*result;

	if (strcmp(s, "\"\"") == 0 || strcmp(s, "\'\'") == 0)
		result = ft_strdup("\n");
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}

char	*heredoc(char *eof)
{
	char	*reslut;
	char	*buf;

	reslut = ft_calloc(sizeof(char *), 1);
	printf("eof = %s\n", eof);
	while (1)
	{
		write(1, ">", 1);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (NULL);
		if (buf && ((strcmp("\n", eof) == 0 && strcmp(eof, buf) == 0)
				|| ft_strncmp(buf, eof, ft_strlen(buf) - 1) == 0))
		{
			free(buf);
			free(eof);
			return (reslut);
		}
		reslut = ft_strjoin_and_free(reslut, buf);
	}
	return (NULL);
}

void	expand_herdoc(t_command_list *com)
{
	t_command_list	*tmp;

	tmp = com->next;
	while (tmp)
	{
		if (tmp->token_type == HEARDOC)
		{
			if (tmp->next->token_type == WORD_IN_DOUBLE_QOUTE
				|| tmp->next->token_type == WORD_IN_SINGLE_QOUTE)
			{
				tmp->next->s = delete_quote_for_heredoc(tmp->next->s);
				tmp->next->token_type = WORD_IN_SINGLE_QOUTE;
			}
			tmp->next->s = heredoc(tmp->next->s);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

void	search_tree_heredoc(t_tree *t)
{
	if (!t)
		return ;
	search_tree_heredoc(t->left);
	search_tree_heredoc(t->right);
	expand_herdoc(t->head);
}
