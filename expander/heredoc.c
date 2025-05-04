/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:01 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 19:20:34 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <signal.h>

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

void	signal_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_interrupt_state = SIGINT;
}

void	set_up_signal_heredoc(void)
{
	struct sigaction	sig;

	sig.sa_handler = signal_heredoc;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
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
		buf = get_next_line(STDIN_FILENO);
		if (g_interrupt_state == SIGINT)
			return (free(reslut), free(eof), (NULL));
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
	return (free(eof), (reslut));
}

void	expand_heredoc(t_token_all *com)
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
				tmp->syntax_error = SIGINT;
				return ;
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}
