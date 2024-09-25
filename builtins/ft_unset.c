/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:02 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 17:47:52 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	var_found(char *to_unset)
{
	t_env	*temp;

	temp = g_data.env_list;
	while (temp)
	{
		if (!ft_strcmp(temp->name, to_unset))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	link_remove(char *to_unset)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter)
	{
		if (!ft_strcmp(iter->name, to_unset))
		{
			if (iter == g_data.env_list)
				g_data.env_list = g_data.env_list->next;
			else
			{
				(iter->next)->prev = (iter)->prev;
				if (iter->next)
					(iter->prev)->next = (iter)->next;
			}
			return ;
		}
		iter = iter->next;
	}
}

void	ft_unset(void)
{
	char	**to_unset;

	to_unset = 0;
	to_unset = g_data.command_list->cmd;
	while (*(++to_unset))
	{
		if (var_found(*to_unset))
			link_remove(*to_unset);
	}
}
