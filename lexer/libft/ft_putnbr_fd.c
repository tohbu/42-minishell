/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:05:27 by tohbu             #+#    #+#             */
/*   Updated: 2024/10/27 14:59:38 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	print;

	print = '0';
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n < 10)
	{
		print = '0' + n;
		write(fd, &print, 1);
		return ;
	}
	else
	{
		print = '0' + n % 10;
		ft_putnbr_fd(n / 10, fd);
		write(fd, &print, 1);
	}
}
