/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:01 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 22:53:15 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_heredoc_warning(char *eof)
{
	int	origin_stdout;

	origin_stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("\nminishell: warning: here-document by end-of-file (wanted `%s')\n",
		eof);
	dup2(origin_stdout, STDOUT_FILENO);
	close(origin_stdout);
	return ;
}

char	*heredoc(char *eof)
{
	char	*reslut;
	char	*buf;
	int		len;

	reslut = ft_calloc(sizeof(char *), 1);
	set_up_signal_heredoc();
	while (1)
	{
		write(STDOUT_FILENO, ">", 1);
		buf = heredoc_readline();
		if (g_interrupt_state == SIGINT)
			return (free(reslut), free(eof), (NULL));
		if (!buf)
			return (print_heredoc_warning(eof), free(eof), (reslut));
		len = ft_strlen(buf);
		buf[len - 1] = '\0';
		if (ft_strcmp(buf, eof) == 0)
			break ;
		buf[len - 1] = '\n';
		reslut = ft_strjoin_and_free(reslut, buf);
	}
	return (free(eof), free(buf), (reslut));
}

void	expand_heredoc(t_token_manager *com)
{
	t_token_list	*tmp;

	tmp = com->head->next;
	while (tmp)
	{
		if (tmp->token_type == HEARDOC)
		{
			if (tmp->next->token_type == WORD_IN_DOUBLE_QOUTE
				|| tmp->next->token_type == WORD_IN_SINGLE_QOUTE)
			{
				tmp->next->token = delete_quote_for_heredoc(tmp->next->token);
				tmp->next->token_type = WORD_IN_SINGLE_QOUTE;
			}
			tmp->next->token = heredoc(tmp->next->token);
			if (g_interrupt_state == SIGINT)
			{
				tmp->error_flag = SIGINT;
				return ;
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

t_bool	heredoc_check(t_token_manager *token)
{
	t_token_list	*tmp;

	tmp = token->head->next;
	while (tmp)
	{
		if (tmp->error_flag == SIGINT)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
