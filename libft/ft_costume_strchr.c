/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_costume_strchr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:09:16 by olaaroub          #+#    #+#             */
/*   Updated: 2024/08/08 12:49:40 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_costume_strchr(const char *str, int c)
{
	size_t	i;
	size_t	j;
	char	*buff;
	char	*ret;

	buff = (char *)str;
	i = 0;
	while (i <= ft_strlen(buff))
	{
		if (buff[i] == (char)c)
			break ;
		i++;
	}
	ret = malloc(sizeof(char) + i + 1);
	j = 0;
	while (j < i)
	{
		ret[j] = buff[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
