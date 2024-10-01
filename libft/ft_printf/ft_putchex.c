/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:55 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:44:22 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchex(int fd, unsigned int l, int *count)
{
	if (l >= 16)
		ft_putchex(fd, l / 16, count);
	ft_putchar(fd, "0123456789ABCDEF"[l % 16], count);
}
