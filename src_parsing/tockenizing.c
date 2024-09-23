/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenizing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:49:20 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/15 18:54:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_type(char *word)
{
	if (ft_strcmp(word, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(word, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(word, ">") == 0)
		return (OUTPUT);
	else if (ft_strcmp(word, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

void	tockenizing(char *line)
{
	char **res;
	int i;
	int type;

	res = split_mgem7a(line);
	if (!res || !*res)
		return ;
	i = 0;
	while (res[i])
	{
		type = check_type(res[i]);
		g_data.tocken_list = ft_add_tocken(res[i], type, false, NULL);
		i++;
	}
}