/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:07:36 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:31:54 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*char_s1;
	unsigned char	*char_s2;

	char_s1 = (unsigned char *)str1;
	char_s2 = (unsigned char *)str2;
	while (n--)
	{
		if (*char_s1 != *char_s2)
			return (*char_s1 - *char_s2);
		char_s1++;
		char_s2++;
	}
	return (0);
}
