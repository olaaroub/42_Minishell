/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockens_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:55:39 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/15 18:53:19 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_tockens	*ft_create_node(char *word, int type, bool ambg, char *dollar)
{
	t_tockens	*new;

	new = (t_tockens *)malloc(sizeof(t_tockens));
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

t_tockens	*ft_add_tocken(char *word, int type, bool ambg, char *dollar)
{
	t_tockens *new;
	t_tockens *temp;

	new = ft_create_node(word, type, ambg, dollar);
	if (!new)
		return (NULL);
	if (!g_data.tocken_list)
		return (new);
	temp = g_data.tocken_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	new->prev = temp;
	return (g_data.tocken_list);
}