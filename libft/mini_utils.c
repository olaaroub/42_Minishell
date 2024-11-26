/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:10:19 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/26 00:37:30 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isset(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	if (c == '$' || c == '@' || c == '*' || c == '#' || c == '-' || c == '!'
		|| ft_isdigit(c))
		return (1);
	return (0);
}

int	words_len(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}
