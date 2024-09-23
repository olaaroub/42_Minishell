/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:22:24 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:31:25 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*char_b;
	unsigned char	d;
	size_t			i;

	char_b = (char *)b;
	d = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		char_b[i] = d;
		i++;
	}
	return (char_b);
}
