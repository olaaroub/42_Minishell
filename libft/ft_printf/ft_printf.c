/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:45:36 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, char const *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			specifier(fd, *(str + 1), args, &count);
			str++;
		}
		else if (*str != '%')
			ft_putchar(fd, *str, &count);
		str++;
	}
	va_end(args);
	return (count);
}
