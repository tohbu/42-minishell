/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:01 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/01 22:17:21 by tomoki-kouk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"


int ft_strcmp(char * s1 , char *s2)
{
	int i = 0;
	if(!s1 || !s2)
		return -1;
		
	while (s1[i] == s2[i])
	{
		if(s1[i] == '\0' && s2[i] =='\0')
			return 0;
		i++;
	}
	return s1[i] -s2[i];
} 

char	*delete_quote_for_heredoc(char *s)
{
	char	*result;

	if (strcmp(s, "\"\"") == 0 || strcmp(s, "\'\'") == 0)
		result = ft_calloc(sizeof(char *), 1);
	else
		result = ft_strndup((s + 1), ft_strlen(s) - 2);
	free(s);
	return (result);
}

char	*heredoc(char *eof)
{
	char	*reslut;
	char	*buf;
	int		len;

	reslut = ft_calloc(sizeof(char *), 1);
	printf("eof = %s\n", eof);
	while (1)
	{
		write(1, ">", 1);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (NULL);
		len = ft_strlen(buf);
		if (len > 0 && buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (ft_strcmp(buf, eof) == 0)
		{
			free(buf);
			break ;
		}
		buf[len - 1] = '\n';
		reslut = ft_strjoin_and_free(reslut, buf);
	}
	free(eof);
	return (reslut);
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
