/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:05:32 by tohbu             #+#    #+#             */
/*   Updated: 2024/10/24 20:21:16 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*result;

	if (nmemb != 0 && (size > __SIZE_MAX__ / nmemb))
		return (NULL);
	result = (char *)malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_memset(result, 0, nmemb * size);
	(void)*result;
	return (result);
}
