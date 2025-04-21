/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:18:36 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/06 14:02:09 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cp;
	size_t	i;

	i = 0;
	cp = (char *)malloc(ft_strlen(s) + 1);
	if (!cp)
		return (NULL);
	while (s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
