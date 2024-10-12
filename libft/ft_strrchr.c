/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:02:29 by olaaroub          #+#    #+#             */
/*   Updated: 2024/08/08 12:17:22 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*buff;

	buff = (char *)s;
	if (c == 0)
	{
		return (buff + ft_strlen(buff));
	}
	i = ft_strlen(buff);
	while (i >= 0)
	{
		if (buff[i] == (char)c)
			return (buff + i);
		i--;
	}
	return (NULL);
}
