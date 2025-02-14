/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:06:08 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/23 05:20:54 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*buff;

	buff = (char *)str;
	i = 0;
	while (i <= ft_strlen(buff))
	{
		if (buff[i] == (char)c)
			return (buff + i + 1);
		i++;
	}
	return (NULL);
}
