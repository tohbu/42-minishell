/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:20:50 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/02 12:55:15 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*reslut;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	reslut = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!reslut)
		return (NULL);
	while (s1[i])
	{
		reslut[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		reslut[i + j] = s2[j];
		j++;
	}
	reslut[i + j] = '\0';
	return (reslut);
}
