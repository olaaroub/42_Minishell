/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:26:42 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:29:00 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **ptr, int k)
{
	int	i;

	i = 0;
	while (i <= k)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static int	count_words(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static void	ft_copy(char *src, char *dest, char c)
{
	while (*src && *src != c)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

static char	**fill_strings(char *str, char **ptr, int count, char c)
{
	int	k;
	int	l;

	k = -1;
	while (++k < count && *str)
	{
		while (*str == c && *str)
			str++;
		l = 0;
		while (str[l] != c && str[l])
			l++;
		ptr[k] = (char *)malloc((l + 1) * sizeof(char));
		if (!ptr[k])
			return (ft_free(ptr, k));
		ft_copy(str, ptr[k], c);
		str += l;
	}
	ptr[k] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**ptr;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	count = count_words(str, c);
	ptr = (char **)malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	ptr = fill_strings(str, ptr, count, c);
	return (ptr);
}
