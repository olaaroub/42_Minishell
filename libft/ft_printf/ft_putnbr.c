/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:44:41 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int fd, long nb, int *count)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar(fd, '-', count);
	}
	if (nb >= 10)
		ft_putnbr(fd, nb / 10, count);
	ft_putchar(fd, nb % 10 + '0', count);
}
