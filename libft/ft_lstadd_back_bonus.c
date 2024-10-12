/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:01:38 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:32:47 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst)
	{
		if (*lst)
		{
			current = *lst;
			while (current)
			{
				if (current->next == NULL)
				{
					current->next = new;
					break ;
				}
				current = current->next;
			}
		}
		else
			*lst = new;
	}
}
