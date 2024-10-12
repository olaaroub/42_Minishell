/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:03 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:44:33 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(int fd, unsigned long l, int *count)
{
	if (l >= 16)
		ft_puthex(fd, l / 16, count);
	ft_putchar(fd, "0123456789abcdef"[l % 16], count);
}
