/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:28 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 04:45:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

int		ft_printf(int fd, char const	*str, ...);

void	specifier(int fd, char spf, va_list args, int *count);
void	ft_unsigned(int fd, unsigned int nb, int *count);
void	ft_putchex(int fd, unsigned int l, int *count);
void	ft_puthex(int fd, unsigned long l, int *count);
void	ft_putptr(int fd, unsigned long l, int *count);
void	ft_putstr(int fd, char *str, int *count);
void	ft_putchar(int fd, char ch, int *count);
void	ft_putnbr(int fd, long nb, int *count);

#endif