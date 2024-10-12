/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:31 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:45:00 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(int fd, char *str, int *count)
{
	if (!str)
		return (ft_putstr(fd, "(null)", count));
	while (*str)
	{
		ft_putchar(fd, *str, count);
		str++;
	}
}
