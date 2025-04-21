/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:28:12 by tohbu             #+#    #+#             */
/*   Updated: 2024/12/24 22:32:03 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	word;
	int	frag;

	frag = 0;
	word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (frag)
			{
				word++;
				frag = 0;
			}
		}
		else if (!frag)
			frag = 1;
		s++;
	}
	if (frag)
		word++;
	return (word);
}

static char	*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(n + 1);
	if (!ret)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	**free_arry(char **result, int j)
{
	while (j >= 0)
		free(result[j--]);
	free(result);
	return (NULL);
}

static char	**sub_split(char *s, char c, char **result, int frag)
{
	char	*memory;
	int		j;

	j = 0;
	memory = s;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (frag)
			{
				result[j] = ft_strndup(memory, s - memory);
				if (result[j++] == NULL)
					return (result);
				frag = 0;
			}
			memory = s + 1;
		}
		else if (!frag)
			frag = 1;
		s++;
	}
	if (frag)
		result[j] = ft_strndup(memory, s - memory);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**arr;
	int		i;

	if (s == NULL || *s == '\0')
		return (NULL);
	i = 0;
	word = count_word(s, c);
	arr = (char **)malloc((word + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (word)
	{
		arr = sub_split((char *)s, c, arr, 0);
		while (i < word)
		{
			if (arr[i] == NULL)
				return (free_arry(arr, i));
			i++;
		}
	}
	if (!arr)
		return (NULL);
	arr[word] = NULL;
	return (arr);
}
