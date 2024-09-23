/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:58:37 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/18 23:02:05 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_exit(char *line, bool val)
{
	free_trash(&g_data.trash_list);
	g_data.ret_value = 0;
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (val)
		exit(EXIT_SUCCESS);
}

int	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
// ls -la> k
int	line_len(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				j += 2;
				i += 2;
			}
			else
			{
				j += 2;
				i++;
			}
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				j += 2;
				i += 2;
			}
			else
			{
				j += 2;
				i++;
			}
		}
		else if (line[i] == '|')
		{
			j += 2;
			i++;
		}
		else
			i++;
	}
	return (j);
}
