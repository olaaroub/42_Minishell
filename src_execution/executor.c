/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/30 03:01:29 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	save_fds()
{
	int	stdin;
	int	stdout;
	int	stderr;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	stderr = dup(STDERR_FILENO);
	printf("%d	%d	%d\n", stdin, stdout, stderr);
}

char	*get_cmd_path(char	**paths)
{
	char	*cmd_path;
	int		i;
	char	*cmd;

	i = -1;
	cmd = 0;
	cmd_path = 0;
	while (paths[++i])
	{
		cmd = ft_strjoin("/", *(g_data.command_list->cmd));
		cmd_path = ft_strjoin(paths[i], cmd);
		if(!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		free(cmd);
	}
	return (NULL);
}

char	**get_paths(void)
{	
	if (!entry_found("PATH") || !get_env_node("PATH"))
		return (NULL);
	return (ft_split(get_env_node("PATH")->value, ':'));
}

int	is_command(t_command *cmd)
{
	char	**paths;
	char	*cmd_path;
	// int		fd;
	
	paths = get_paths();
	if (!paths)
		return (-1);
	cmd_path = get_cmd_path(paths);
	save_fds();
	if (execute_cmd(cmd_path, cmd))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(), 1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(), 1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(), 1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(), 1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(), 1);
	// else if (!ft_strncmp(cmd, "export", 6))
	// 	return (ft_export(), 1);
	return (0);
}
void	executor(void)
{
	t_command	*cmd;
	int			keeper;
	
	cmd = 0;
	keeper = -1;
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd)
		return ;
	printf("file name ---> %s\n", cmd->red->file_name);
	while (cmd)
	{
		if (!is_builtin(*cmd->cmd) && !is_command(cmd))
			printf("%s: command not found", *cmd->cmd);
		cmd = cmd->next;
	}
	if (entry_found("_"))
		update_var("_", g_data.command_list->cmd[0]);
}
