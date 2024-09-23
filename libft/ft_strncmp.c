/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:22:29 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:58:44 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *str1, char *str2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if ((!s1 && !s2) || n == 0)
		return (0);
	while ((s2[i] != '\0' && s1[i] != '\0') && (s1[i] == s2[i]) && i < n - 1)
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
