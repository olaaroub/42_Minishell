/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/01 06:25:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd(t_command *cmd, char c)
{
	int fd;

	fd = 0;
	if (cmd->red)
	{
		if (cmd->red->type == INPUT)
			fd = open(cmd->red->file_name, O_RDONLY);
		else if (cmd->red->type == HEREDOC)
			fd = open("", O_CREAT | O_RDWR | O_APPEND);
		else if (cmd->red->type == OUTPUT)
			fd = open(cmd->red->file_name, O_CREAT | O_WRONLY | O_TRUNC);
		else if (cmd->red->type == APPEND)
			fd = open(cmd->red->file_name, O_CREAT | O_WRONLY |O_APPEND);
	}
	else
		fd = 1 * (c == 'o');
	if (fd == -1)
		ft_putendl_fd(strerror(errno), 2);
	return (fd);
}

void	child_proc(t_command *cmd, char *cmd_path, int in, int out)
{
	printf("in == %d\tout == %d\n", in, out);
	if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
		ft_printf(2, "dup2: %s\n", strerror(errno));
	close(in);
	close(out);
	if (execve(cmd_path, cmd->cmd, NULL) == -1)
		ft_printf(2, "execve: %s\n", strerror(errno));	
}

int	execute_cmd(char *cmd_path, t_command *cmd, int *keeper)
{
	/*Will need to fix the problems resulting from this*/
	int	pid;
	int	pipefd[2];
	int	in;
	int	out;

	in = *keeper;
	out = 1;
	if(cmd->next && !cmd->red)
	{
		printf("cmd == %s\n", *cmd->cmd);
		pipe(pipefd);
		out = pipefd[1];
	}
	else
	{
		printf("cmd == %s\n", *cmd->cmd);
		in = get_fd(cmd, 'i');
		out = get_fd(cmd, 'o');
	}
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child_proc(cmd, cmd_path, in, out);
	else
	{
		close(in);
		close(out);
		if (cmd->next && !cmd->red)
			*keeper = pipefd[0];
	}
	return (1);
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

int	is_command(t_command *cmd, int *keeper)
{
	char	**paths;
	char	*cmd_path;
	
	paths = get_paths();
	if (!paths)
		return (-1);
	cmd_path = get_cmd_path(paths);
	if (!cmd_path)
		return (0);
	return (execute_cmd(cmd_path, cmd, keeper));
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
	static int	keeper;
	
	keeper = 0;
	cmd = 0;
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd)
		return ;
	while (cmd)
	{
		if (!is_builtin(*cmd->cmd) && !is_command(cmd, &keeper))
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
		printf("keeper == %d\n", keeper);
		cmd = cmd->next;
	}
}
