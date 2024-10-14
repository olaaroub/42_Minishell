/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:27:07 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:43:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	specifier(int fd, char spf, va_list args, int *count)
{
	if (spf == 's')
		ft_putstr(fd, va_arg(args, char *), count);
	else if (spf == 'c')
		ft_putchar(fd, va_arg(args, int), count);
	else if (spf == 'd')
		ft_putnbr(fd, va_arg(args, int), count);
	else if (spf == 'i')
		ft_putnbr(fd, va_arg(args, int), count);
	else if (spf == 'u')
		ft_unsigned(fd, va_arg(args, unsigned int), count);
	else if (spf == 'x')
		ft_puthex(fd, va_arg(args, unsigned int), count);
	else if (spf == 'X')
		ft_putchex(fd, va_arg(args, unsigned int), count);
	else if (spf == 'p')
		ft_putptr(fd, va_arg(args, unsigned long), count);
	else
		ft_putchar(fd, spf, count);
}
