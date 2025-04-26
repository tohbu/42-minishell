/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:48:48 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/25 16:19:01 by tomoki-kouk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lexer.h"
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

int	ft_getchar(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp = NULL;
	static int	n = 0;
	static int	eof_frag = 0;

	if (eof_frag)
		return (END);
	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (END);
		if (n == 0)
		{
			if (bufp == NULL || *--bufp == '\n')
				return (END);
			eof_frag = 1;
		}
		bufp = buf;
	}
	if (!eof_frag && n-- >= 0)
		return ((unsigned char)*bufp++);
	return (EOF);
}

char	*get_next_line(int fd)
{
	char	*tmp;
	int		i;
	int		k;

	if (fd < 0 || fd > _SC_OPEN_MAX)
		return (NULL);
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
		tmp[i] = ft_getchar(fd);
		if (tmp[i] == END)
			return (free(tmp), NULL);
		if (tmp[i] == '\n' || tmp[i] == EOF)
			return (ft_strdup_extra(tmp));
		i++;
	}
}
