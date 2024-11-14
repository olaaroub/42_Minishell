/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:45 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/13 17:53:49 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_pwd(void)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter)
	{
		if (!ft_strcmp(iter->name, "PWD"))
			return (iter->value);
		iter = iter->next;
	}
	return (NULL);
}

int	entry_found(char *to_find)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter && to_find)
	{
		if (!ft_strcmp(iter->name, to_find))
			return (1);
		iter = iter->next;
	}
	return (0);
}

t_env	*get_env_node(char *to_find)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter && to_find)
	{
		if (!ft_strcmp(iter->name, to_find))
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

// /*		This Function Can work with export*/
void	update_var(char *to_find, char *new_value)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter)
	{
		if (!ft_strcmp(iter->name, to_find))
		{
			if (iter->value)
				free (iter->value);
			iter->value = ft_strdup(new_value);
		}
		iter = iter->next;
	}
}

void	ft_cd(void)
{
	char		*path;
	t_command	*cmd;

	cmd = g_data.command_list;
	if (!cmd->cmd[1])
		return ;
	if (cmd->cmd[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_data.ret_value = 1;
		return ;
	}
	path = cmd->cmd[1];
	if (chdir(path) == -1)
	{
		g_data.ret_value = 1;
		return (ft_printf(2, " %s", strerror(errno)), (void)NULL);
	}
}
