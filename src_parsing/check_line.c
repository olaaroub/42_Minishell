/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:18:01 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/13 23:41:37 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_white_spaces(char *line)
{
	int		i;
	int		j;
	int		len;
	char	quote_char;

	quote_char = '\0';
	i = 0;
	j = 0;
	if (!line)
		return ;
	len = ft_strlen(line);
	while (is_whitespace(line[i]))
		i++;
	while (i < len)
	{
		if ((line[i] == '"' || line[i] == '\'') && quote_char == '\0')
		{
			quote_char = line[i];
			line[j++] = line[i++];
		}
		else if (line[i] == quote_char)
		{
			quote_char = '\0';
			line[j++] = line[i++];
		}
		else if (quote_char == '\0' && is_whitespace(line[i]))
		{
			line[j++] = ' ';
			while (i < len && is_whitespace(line[i]))
				i++;
		}
		else
		{
			line[j++] = line[i++];
		}
	}
	if (j > 0 && is_whitespace(line[j - 1]) && quote_char == '\0')
		j--;
	line[j] = '\0';
}

int count_single_quotes(char *line, size_t *i)
{
	int s_quotes;

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

int count_double_quotes(char *line, size_t *i)
{
	int d_quotes;

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

int	valid_quotes(char *line)
{
	size_t	i;
	int	d_quotes;
	int	s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	if (!line)
		return (2);
	i = 0;
	while (is_whitespace(line[i]))
		i++;
	while (i < ft_strlen(line))
	{
		s_quotes += count_single_quotes(line, &i);
		d_quotes += count_double_quotes(line, &i);
		if(line[i] != 39 && line[i] != 34)
			i++;
	}
	if ((s_quotes % 2 != 0) || (d_quotes % 2 != 0))
		return (0);
	return (2);
}

void write_spaces(char *line, char *buff, int *i, int *j)
{
	char quote;

	quote = '\0';
	if ((line[*i] == '\'' || line[*i] == '"') && quote == '\0')
		{
			quote = line[*i];
			buff[(*j)++] = line[(*i)++];
		}
		else if (line[(*i)] == quote)
		{
			quote = '\0';
			buff[(*j)++] = line[(*i)++];
		}
		else if ((line[(*i)] == '>'  || line[(*i)] == '<' || line[(*i)] == '|') && quote == '\0')
		{
			buff[(*j)++] = ' ';
			buff[(*j)++] = line[(*i)++];
			if (line[(*i)] == buff[(*j)-1] && (buff[(*j)-1] == '>' || buff[(*j)-1] == '<'))
				buff[(*j)++] = line[(*i)++];
			buff[(*j)++] = ' ';
		}
		else
			buff[(*j)++] = line[(*i)++];
}

char	*add_space(char *line)
{
	int		i;
	int		j;
	char	*buff;
	int		len;

	i = 0;
	j = 0;
	if(!line)
		return NULL;
	len = ft_strlen(line) + line_len(line);
	buff = malloc(sizeof(char) * len + 1);
	while (line[i])
		write_spaces(line, buff, &i, &j);
	buff[j] = '\0';
	free(line);
	return (buff);
}
