/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:53:19 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/03 19:21:36 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_trash	*ft_create_node(void *addr)
{
	t_trash	*new;

	new = (t_trash *)malloc(sizeof(t_trash));
	if (!new)
		return (NULL);
	new->address = addr;
	new->next = NULL;
	return (new);
}

t_trash	*ft_add_trash(t_trash **head, void *addr)
{
	t_trash	*new;
	t_trash	*temp;

	new = ft_create_node(addr);
	if (!new)
		return (NULL);
	if (!*head)
		return (new);
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	return (*head);
}

void	free_trash(t_trash **head)
{
	t_trash	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if(tmp->address)
			free(tmp->address);
		free(tmp);
	}
}
