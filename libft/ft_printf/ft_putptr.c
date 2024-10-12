/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:19 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:44:50 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(int fd, unsigned long l, int *count)
{
	ft_putstr(fd, "0x", count);
	if (l >= 16)
		ft_puthex(fd, l / 16, count);
	ft_putchar(fd, "0123456789abcdef"[l % 16], count);
}
