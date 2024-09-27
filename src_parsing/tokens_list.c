/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:55:39 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/27 13:28:17 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tokens	*token_node(char *word, int type, bool ambg, char *dollar)
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

t_tokens	*ft_add_token(char *word, int type, bool ambg, char *dollar)
{
	t_tokens *new;
	t_tokens *temp;

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