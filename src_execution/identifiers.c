/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:07:16 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/19 20:07:31 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_command(t_command *cmd, char **paths)
{
	char	*cmd_path;

	if (!paths)
		return (-1);
	cmd_path = get_cmd_path(cmd, paths);
	if (!cmd_path)
		return (0);
	return (1);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}
