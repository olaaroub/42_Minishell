/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 18:46:40 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	executor(void)
{
	char	*cmd;

	cmd = 0;
	if(!g_data.command_list)
		return;
	cmd = g_data.command_list->cmd[0];
	if(!cmd || !*cmd) // fixed segfault when cmd expands to NULL ex: $XX
		return;
	if (!ft_strncmp(cmd, "cd", 2))
		ft_cd();
	else if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd, "env", 3))
		ft_env();
	else if (!ft_strncmp(cmd, "unset", 5))
		ft_unset();
	else if (!ft_strncmp(cmd, "echo", 4))
		ft_echo();
}
