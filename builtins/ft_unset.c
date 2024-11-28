/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:02 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/28 19:42:51 by hatalhao         ###   ########.fr       */
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
				(iter->prev)->next = (iter)->next;
				if (iter->next)
					(iter->next)->prev = iter->prev;
			}
			free(iter->line);
			free(iter->name);
			free(iter->value);
			return (free(iter));
		}
		iter = iter->next;
	}
}

void	ft_unset(t_command *cmd)
{
	char	**to_unset;

	to_unset = cmd->cmd;
	while (*(++to_unset))
	{
		if (var_found(*to_unset))
			link_remove(*to_unset);
	}
}
