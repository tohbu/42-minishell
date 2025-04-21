/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:57 by tohbu             #+#    #+#             */
/*   Updated: 2024/10/24 17:35:27 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	d;
	unsigned char	*p;

	p = (unsigned char *)s;
	d = (unsigned char)c;
	while (n-- > 0)
		*p++ = d;
	return (s);
}
