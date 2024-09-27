/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/27 09:43:55 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	is_command(char *cmd)
// {
		
// }

void	is_builtin(char *cmd)
{	
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
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exit();
	// else if (!ft_strncmp(cmd, "export", 6))
	// 	ft_export();
	if (entry_found("_"))
		update_var("_", g_data.command_list->cmd[0]);
}
void	executor(void)
{
	char	*cmd;
	
	cmd = 0;
	if(!g_data.command_list)
		return;
	cmd = g_data.command_list->cmd[0];
	is_builtin(cmd);
	// is_command(cmd);

}