/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:49:20 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/15 18:54:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_tokens	*token_node(char *word, int type, bool ambg, char *dollar)
{
	t_tokens	*new;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new);
	if (!new)
		return (NULL);
	new->word = word;
	new->type = type;
	new->word_after_exp = NULL;
	new->ambiguous = ambg;
	new->dollar = dollar;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_tokens	*ft_add_token(char *word, int type, bool ambg, char *dollar)
{
	t_tokens	*new;
	t_tokens	*temp;

	new = token_node(word, type, ambg, dollar);
	if (!new)
		return (NULL);
	if (!g_data.token_list)
		return (new);
	temp = g_data.token_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	new->prev = temp;
	return (g_data.token_list);
}

static int	check_type(char *word)
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

void	tokenizing(char *line)
{
	char	**res;
	int		i;
	int		type;

	res = customized_split(line);
	if (!res || !*res)
		return ;
	i = 0;
	while (res[i])
	{
		type = check_type(res[i]);
		g_data.token_list = ft_add_token(res[i], type, false, NULL);
		i++;
	}
}
