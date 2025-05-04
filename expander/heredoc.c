/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:01 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 16:19:02 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
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
	while (1)
	{
		write(1, ">", 1);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (print_heredoc_warning(eof), free(eof), (reslut));
		len = ft_strlen(buf);
		if (buf[len - 1] == '\n')
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

void	expand_heredoc(t_command_list *com)
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
