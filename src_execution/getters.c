/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/19 17:06:38 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd_path(t_command *cmd, char	**paths)
{
	char	*cmd_path;
	int		i;
	char	*tmp;

	i = -1;
	tmp = 0;
	cmd_path = 0;
	tmp = ft_strjoin("/", *cmd->cmd);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], tmp);
		if(!access(cmd_path, X_OK))
			return (free (tmp), cmd_path);
		free(cmd_path);
	}
	free(tmp);
	return (NULL);
}

char	**get_paths(void)
{	
	if (!entry_found("PATH") || !get_env_node("PATH"))
		return (NULL);
	return (ft_split(get_env_node("PATH")->value, ':'));
}
