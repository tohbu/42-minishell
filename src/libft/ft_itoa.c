/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:28:31 by tohbu             #+#    #+#             */
/*   Updated: 2024/11/06 14:02:45 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	itolen(int n)
{
	size_t	result;

	result = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		result++;
		n /= 10;
	}
	return (result);
}

static char	*sub_itoa(char *result, long int n, size_t sign, size_t length)
{
	size_t	i;

	i = 0;
	if (sign)
		result[0] = '-';
	while (i < length)
	{
		result[(length + sign - 1) - i++] = (n % 10) + '0';
		n /= 10;
	}
	result[length + sign] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		sign;
	size_t		length;
	long int	n_tmp;

	n_tmp = (long int)n;
	length = itolen(n);
	sign = 0;
	if (n_tmp < 0)
	{
		sign++;
		n_tmp = n_tmp * -1;
	}
	result = (char *)malloc(length + sign + 1);
	if (!result)
		return (NULL);
	return (sub_itoa(result, n_tmp, sign, length));
}
