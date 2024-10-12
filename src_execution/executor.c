/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/09 21:33:25 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// int	execute_cmd(char *cmd_path, t_command *cmd)
// {
// 	/*Will need to enhance the logic in here to avoid redundant code*/
// 	int	pid;
// 	int	pipefd[2];
// 	int	in;
// 	int	out;
// 	int keeper;

// 	if (cmd->red->type == PIPE)
// 	{
// 		pipe(pipefd);
// 		in = pipefd[0];
// 		out = pipefd[1];
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
// 			ft_putendl_fd(strerror(errno), 2);
// 		close(in);
// 		close(out);
// 		if (execve(cmd_path, g_data.command_list->cmd, NULL) == -1)
// 			ft_putendl_fd("execve failed", 2);
// 	}
// 	else
// 	{
// 		close(in);
// 		close(cmd->red);
// 		if (cmd->red->type == PIPE)
// 			keeper = pipefd[0];

// 	}
// }

// char	*get_cmd_path(char	**paths)
// {
// 	char	*cmd_path;
// 	int		i;
// 	char	*cmd;

// 	i = -1;
// 	cmd = 0;
// 	cmd_path = 0;
// 	while (paths[++i])
// 	{
// 		cmd = ft_strjoin("/", *(g_data.command_list->cmd));
// 		cmd_path = ft_strjoin(paths[i], cmd);
// 		if(!access(cmd_path, X_OK))
// 			return (cmd_path);
// 		free(cmd_path);
// 		free(cmd);
// 	}
// 	return (NULL);
// }

// char	**get_paths(void)
// {
// 	if (!entry_found("PATH") || !get_env_node("PATH"))
// 		return (NULL);
// 	return (ft_split(get_env_node("PATH")->value, ':'));
// }

// int	is_command(t_command *cmd)
// {
// 	char	**paths;
// 	char	*cmd_path;
// 	int		fd;

// 	paths = get_paths();
// 	if (!paths)
// 		return (-1);
// 	cmd_path = get_cmd_path(paths);

// 	if (execute_cmd(cmd_path, cmd));
// 		return (1);
// 	return (0);
// }

int	is_builtin(char **cmd)
{
	// if (!ft_strncmp(cmd, "cd", 2))
	// 	return (ft_cd(), 1);
	// else if (!ft_strncmp(cmd, "pwd", 3))
	// 	return (ft_pwd(), 1);
	// else if (!ft_strncmp(cmd, "env", 3))
	// 	return (ft_env(), 1);
	// else if (!ft_strncmp(cmd, "unset", 5))
	// 	return (ft_unset(), 1);
	// else if (!ft_strncmp(cmd, "echo", 4))
	// 	return (ft_echo(), 1);
	// else if (!ft_strncmp(cmd, "exit", 4))
	// 	return (ft_exit(), 1);
	if (!ft_strncmp(cmd[0], "export", 6))
		return (ft_export(cmd), 1);
	return (0);
}
void	executor(void)
{
	t_command	*cmd;

	cmd = 0;
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd)
		return ;
	while (cmd)
	{
		if (!is_builtin(cmd->cmd))
			printf("%s: command not found", *cmd->cmd);
		cmd = cmd->next;
	}
	// if (entry_found("_"))
	// 	update_var("_", g_data.command_list->cmd[0]);
}
