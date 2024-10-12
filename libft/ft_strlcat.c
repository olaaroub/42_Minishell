/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:27 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:28:32 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	slenght;
	size_t	dlenght;

	if (!size && !dest)
		return (ft_strlen(src));
	dlenght = ft_strlen(dest);
	slenght = ft_strlen(src);
	if (size == 0 || size <= dlenght)
		return (size + slenght);
	j = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dlenght + slenght);
}
