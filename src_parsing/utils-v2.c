/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:08:03 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/14 11:59:26 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	len_until_pipe(t_tokens *temp)
{
	t_tokens	*tmp;
	int			i;
	int			j;

	i = 0;
	tmp = temp;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->word_after_exp && tmp->word_after_exp[1])
		{
			j = 0;
			while (tmp->word_after_exp[j])
			{
				j++;
				i++;
			}
		}
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	split_tokens(void)
{
	t_tokens	*tmp;

	tmp = g_data.token_list;
	while (tmp)
	{
		tmp->word_after_exp = split_mgem7a(tmp->word);
		tmp = tmp->next;
	}
}

void	free_env_list(void)
{
	t_env	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		free(tmp->line);
		free(tmp->name);
		free(tmp->value);
		tmp = tmp->next;
		free(g_data.env_list);
		g_data.env_list = tmp;
	}
}

void	skip_d_quotes(char *line, int *i)
{
	int	d_quotes;

	d_quotes = 0;
	while (line[(*i)])
	{
		if (line[(*i)] == 34)
			d_quotes++;
		i++;
		if (d_quotes % 2 == 0)
			break ;
	}
}

void	skip_s_quotes(char *line, int *i)
{
	int	s_quotes;

	s_quotes = 0;
	while (line[(*i)])
	{
		if (line[(*i)] == 39)
			s_quotes++;
		(*i)++;
		if (s_quotes % 2 == 0)
			break ;
	}
}
