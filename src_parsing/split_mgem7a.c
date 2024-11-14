/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mgem7a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:44:35 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/14 11:59:20 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*escape_quotes(char *line)
{
	int	quotes;

	quotes = 0;
	if (*line == 34)
	{
		while (*line && quotes != 2)
		{
			if (*line == 34)
				quotes++;
			line++;
		}
	}
	else if (*line == 39)
	{
		while (*line && quotes != 2)
		{
			if (*line == 39)
				quotes++;
			line++;
		}
	}
	return (line);
}

int	word_lenght(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_whitespace(line[i]))
	{
		if (line[i] == 34)
			skip_d_quotes(line, &i);
		else if (line[i] == 39)
			skip_s_quotes(line, &i);
		else
			i++;
	}
	return (i);
}

static int	count_words(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line && is_whitespace(*line))
			line++;
		if (*line && !is_whitespace(*line))
		{
			count++;
			while (*line && !is_whitespace(*line))
			{
				if (*line == 34 || *line == 39)
					line = escape_quotes(line);
				else
					line++;
			}
		}
	}
	return (count);
}

static char	**fill_strings(char *line, char **result, int count)
{
	int	k;
	int	l;

	k = 0;
	while (k < count && *line)
	{
		while (is_whitespace(*line) && *line)
			line++;
		l = word_lenght(line);
		result[k] = (char *)malloc((l + 1) * sizeof(char));
		g_data.trash_list = ft_add_trash(&g_data.trash_list, result[k]);
		if (!result[k])
			return (NULL);
		ft_strlcpy(result[k], line, l + 1);
		line += l;
		k++;
	}
	result[k] = 0;
	return (result);
}

char	**split_mgem7a(char *line)
{
	char	**result;
	char	*buff;
	int		count;

	if (!line)
		return (NULL);
	buff = line;
	count = count_words(buff);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, result);
	if (!result)
		return (NULL);
	result = fill_strings(line, result, count);
	return (result);
}
