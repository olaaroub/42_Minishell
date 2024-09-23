/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:04:32 by olaaroub          #+#    #+#             */
/*   Updated: 2023/11/22 21:48:55 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cmp;
	t_list	*ptr;

	ptr = lst;
	cmp = 0;
	while (ptr)
	{
		cmp++;
		ptr = ptr->next;
	}
	return (cmp);
}
