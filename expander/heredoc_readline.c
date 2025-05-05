/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:48:48 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 22:50:37 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup_extra(char *s)
{
	char	*cp;
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != EOF)
		i++;
	if (s[i] == '\n')
		s[i + 1] = '\0';
	if (s[i] == EOF)
		s[i] = '\0';
	cp = (char *)malloc(ft_strlen(s) + 1);
	if (!cp)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	free(s);
	return (cp);
}

char	*exted_buf(char *s, int k)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(TEMP_BUF_SIZE * (k + 1));
	if (!result)
	{
		free(s);
		return (NULL);
	}
	while (i < TEMP_BUF_SIZE * k)
	{
		result[i] = s[i];
		i++;
	}
	free(s);
	return (result);
}

int	ft_getc(int fd)
{
	char	s[1];
	int		reslut;

	s[0] = '\0';
	(void)fd;
	reslut = read(STDIN_FILENO, s, 1);
	if (reslut == -1 && errno == EINTR)
		return (END);
	if (reslut == 0)
		return (EOF);
	else
		return (s[0]);
}

char	*heredoc_readline(void)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = (char *)malloc(TEMP_BUF_SIZE);
	if (!tmp)
		return (NULL);
	i = 0;
	k = 1;
	while (1)
	{
		if (i >= TEMP_BUF_SIZE * k - 1)
			tmp = exted_buf(tmp, k++);
		if (!tmp)
			return (NULL);
		tmp[i] = ft_getc(STDIN_FILENO);
		if (tmp[i] == END || (tmp[i] == EOF && i == 0))
			return (free(tmp), NULL);
		if (tmp[i] == EOF && i != 0)
			continue ;
		if (tmp[i] == '\n')
			return (ft_strdup_extra(tmp));
		i++;
	}
}
