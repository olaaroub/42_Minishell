/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:59:28 by olaaroub          #+#    #+#             */
/*   Updated: 2024/08/16 21:30:23 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*ft_strtrim(char const *s1)
{
	char	*ptr;
	char	*buff;
	size_t	i;
	size_t	j;

	i = 0;
	if (s1)
	{
		j = ft_strlen(s1);
		if (j == 0)
			return (ft_strdup(""));
		while (s1[i] && is_whitespace(s1[i]))
			i++;
		while (s1[j - 1] && j > i && is_whitespace(s1[j - 1]))
			j--;
		ptr = malloc(j - i + 1);
		if (!ptr)
			return (NULL);
		buff = ptr;
		ft_strlcpy(buff, s1 + i, j - i + 1);
		return (ptr);
	}
	return (NULL);
}
