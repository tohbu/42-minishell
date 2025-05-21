/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:46 by tohbu             #+#    #+#             */
/*   Updated: 2024/10/30 18:27:51 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_s;
	size_t	src_s;

	dst_s = ft_strlen(dst);
	src_s = ft_strlen(src);
	if (size <= dst_s)
	{
		return (size + src_s);
	}
	size = size - dst_s;
	while (*dst != '\0')
	{
		dst++;
	}
	while (*src != '\0' && size > 1)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (dst_s + src_s);
}
