/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:45 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/06 22:37:49 by hatalhao         ###   ########.fr       */
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
	char	*path;
	char	*new_pwd;

	new_pwd = 0;
	if (!g_data.command_list->cmd[1])
		return ;
	path = g_data.command_list->cmd[1];
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
	// The Function that export will use to add a node to the env
	if (entry_found("OLDPWD") && entry_found("PWD"))
		update_var("OLDPWD", get_pwd());
	// The Function that export will use to add a node to the env
	if (entry_found("PWD"))
		update_var("PWD", getcwd(new_pwd, 0));
}

/*	Will need to update OLDPWD in ENV before changing the directory	*/
/*	If one of OLDPWD or PWD has been unset, it will have to be added to the env,
PWD Should be filled with the current directory, OLDPWD should have the parent directory*/ 
