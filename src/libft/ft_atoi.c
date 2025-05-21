/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:40:16 by tohbu             #+#    #+#             */
/*   Updated: 2024/12/24 22:53:08 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	atoi_sub(char *s, int sign)
{
	long int	result;

	result = 0;
	while ((*s >= '0' && *s <= '9'))
	{
		if (sign == 1 && result > (LONG_MAX - (*s - '0')) / 10)
			return (LONG_MAX);
		else if (sign == -1 && (-result < (LONG_MIN + (*s - '0')) / 10))
			return (LONG_MIN);
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}

long	ft_atoi(const char *nptr)
{
	int	negative;

	negative = 1;
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r' || *nptr == '\t'
		|| *nptr == '\v' || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative = -1;
		nptr++;
	}
	return (atoi_sub((char *)nptr, negative));
}
