/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:51:37 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/06 14:01:54 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp1;
	const unsigned char	*tmp2;
	size_t				i;

	tmp1 = (const unsigned char *)s1;
	tmp2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (tmp1[i] > tmp2[i])
			return (1);
		if (tmp1[i] < tmp2[i])
			return (-1);
		i++;
	}
	return (0);
}
