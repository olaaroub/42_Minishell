/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:50:16 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:30:53 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
	{
		if (n == -2147483648)
			ft_putstr_fd("-2147483648", fd);
		else
		{
			if (n < 0)
			{
				ft_putchar_fd('-', fd);
				n = -n;
			}
			if (n >= 10)
			{
				ft_putnbr_fd(n / 10, fd);
				ft_putchar_fd(48 + n % 10, fd);
			}
			else
				ft_putchar_fd(n + 48, fd);
		}
	}
}
