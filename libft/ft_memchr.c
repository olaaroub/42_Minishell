/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:31:08 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:32:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*found_char;
	size_t			i;

	p = (unsigned char *)s;
	found_char = NULL;
	i = 0;
	while (n--)
	{
		if (p[i] != (unsigned char)c)
			i++;
		else
		{
			found_char = p + i;
			break ;
		}
	}
	return (found_char);
}
