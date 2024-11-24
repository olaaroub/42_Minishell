/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:45 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/18 03:27:45 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*to_go(t_command *cmd, char *path)
{
	t_env	*home;

	if (!cmd->cmd[1])
	{
		home = get_env_node("HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_data.ret_value = 1;
			return (NULL);
		}
		return (home->value);
	}
	else if (cmd->cmd[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_data.ret_value = 1;
		return (NULL);
	}
	path = cmd->cmd[1];
	return (path);
}

void	ft_cd(t_command *cmd)
{
	char		*path;

	path = 0;
	path = to_go(cmd, path);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		g_data.ret_value = 1;
		return (ft_printf(2, "minishell: cd: %s\n", \
		strerror(errno)), (void) NULL);
	}
}
