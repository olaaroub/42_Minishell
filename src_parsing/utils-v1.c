/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:58:37 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/14 12:00:00 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_exit(char *line, bool val)
{
	free_trash(&g_data.trash_list);
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (val)
		exit(EXIT_SUCCESS);
}

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
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			j += 2;
			if (line[i + 1] == line[i])
				i += 2;
			else
				i++;
		}
		else
			i++;
	}
	return (j);
}

int	count_single_quotes(char *line, size_t *i)
{
	int	s_quotes;

	s_quotes = 0;
	if (line[*i] == 39)
	{
		s_quotes++;
		(*i)++;
		while (line[*i])
		{
			if (line[*i] == 39)
			{
				s_quotes++;
				(*i)++;
				break ;
			}
			(*i)++;
		}
	}
	return (s_quotes);
}

int	count_double_quotes(char *line, size_t *i)
{
	int	d_quotes;

	d_quotes = 0;
	if (line[*i] == 34)
	{
		d_quotes++;
		(*i)++;
		while (line[*i])
		{
			if (line[*i] == 34)
			{
				d_quotes++;
				(*i)++;
				break ;
			}
			(*i)++;
		}
	}
	return (d_quotes);
}

size_t	list_size(void *lst, int s)
{
	size_t		x;
	t_env		*lst1;
	t_command	*lst2;

	x = 0;
	if (s)
		lst1 = (t_env *)lst;
	if (!s)
		lst2 = (t_command *)lst;
	while (s && lst1)
	{
		x++;
		lst1 = lst1->next;
	}
	while (!s && lst2)
	{
		x++;
		lst2 = lst2->next;
	}
	return (x);
}
