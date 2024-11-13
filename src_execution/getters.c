/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/11 18:12:18 by hatalhao         ###   ########.fr       */
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
	if (!*cmd->cmd)
		return (NULL);
	if (*cmd->cmd[++i] == '/' || *cmd->cmd[i] == '.')
		return (ft_strdup(*cmd->cmd));
	tmp = ft_strjoin("/", *cmd->cmd);
	while (paths && paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], tmp);
		if (!access(cmd_path, X_OK))
			return (free (tmp), cmd_path);
		free (cmd_path);
	}
	free (tmp);
	return (ft_strdup(*cmd->cmd));
}

char	**get_paths(void)
{
	if (!entry_found("PATH") || !get_env_node("PATH"))
		return (NULL);
	return (ft_split(get_env_node("PATH")->value, ':'));
}
