/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:18:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/17 02:19:26 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*get_cmd_path(t_command *cmd, char	**paths)
{
	char	*cmd_path;
	int		i;
	char	*tmp;

	i = -1;
	tmp = 0;
	cmd_path = 0;
	if (!*cmd->cmd || **cmd->cmd == '\0')
		return (NULL);
	if (*cmd->cmd[++i] == '/' || *cmd->cmd[i] == '.')
		return (ft_strdup(*cmd->cmd));
	tmp = ft_strjoin("/", *cmd->cmd);
	while (paths && paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], tmp);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
			return (free (tmp), cmd_path);
		free (cmd_path);
	}
	free (tmp);
	return (NULL);
}

char	**get_paths(void)
{
	if (!entry_found("PATH"))
		return (NULL);
	return (ft_split(get_env_node("PATH")->value, ':'));
}
