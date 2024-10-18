/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/18 13:18:52 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd_path(char	**paths)
{
	char	*cmd_path;
	int		i;
	char	*cmd;

	i = -1;
	cmd = 0;
	cmd_path = 0;
	cmd = ft_strjoin("/", *(g_data.command_list->cmd));
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if(!access(cmd_path, X_OK))
			return (free (cmd), cmd_path);
		free(cmd_path);
	}
	free(cmd);
	return (NULL);
}

char	**get_paths(void)
{	
	if (!entry_found("PATH") || !get_env_node("PATH"))
		return (NULL);
	return (ft_split(get_env_node("PATH")->value, ':'));
}
