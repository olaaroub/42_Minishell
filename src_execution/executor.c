/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/12 12:31:37 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_proc(t_command *cmd, char *cmd_path, int in, int out)
{
	printf("in == %d\tout == %d\n", in, out);
	if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
		ft_printf(2, "dup2: %s\n", strerror(errno));
	ft_close(in);
	if (cmd->next)
		ft_close(out);
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
	if (cmd->next)
	{
		printf("cmd == %s\n", *cmd->cmd);
		pipe(pipefd);
		out = pipefd[1];
	}
	else
	{
		printf("cmd == %s\n", *cmd->cmd);
		in = *keeper;
		out = get_fd(cmd, 'o');
	}
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child_proc(cmd, cmd_path, in, out);
	else
	{
		ft_close(in);
		ft_close(out);
		if (cmd->next && !cmd->red)
			*keeper = pipefd[0];
	}
	return (1);
}

void	execute_input(t_command *cmd, char	**paths, int *keeper)
{
	char	*cmd_path;

	cmd_path = 0;
	while (cmd)
	{
		
		execute_cmd(cmd_path, cmd, keeper);
	}
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
	if (cmd->next)
	{
		printf("cmd == %s\n", *cmd->cmd);
		pipe(pipefd);
		out = pipefd[1];
	}
	else
	{
		printf("cmd == %s\n", *cmd->cmd);
		in = *keeper;
		// out = get_fd(cmd, 'o');
	}
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child_proc(cmd, cmd_path, in, out);
	else
	{
		// ft_close(in);
		// ft_close(out);
		if (cmd->next && !cmd->red)
			*keeper = pipefd[0];
	}
	return (1);

}

// void	execute_input(t_command *cmd, char	**paths, int *keeper)
// {
// 	// while (cmd)
// 	// execute_cmd(cmd_path, cmd, keeper);
// }

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

int	is_command(t_command *cmd, char **paths)
{
	char	*cmd_path;

	if (!paths)
		return (-1);
	cmd_path = get_cmd_path(paths);
	if (!cmd_path)
		return (0);
	return (1);
}


int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (1);
	return (0);
}

void	execute_builtin(t_command *cmd)
{
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (cmd->red)
		set_redirections(&in_fd, &out_fd, cmd);
	dup_redirections(in_fd, out_fd);
	if (!ft_strncmp(cmd->cmd, "cd", 2))
		ft_cd();
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd->cmd, "env", 3))
		ft_env();
	else if (!ft_strncmp(cmd->cmd, "unset", 5))
		ft_unset();
	else if (!ft_strncmp(cmd->cmd, "echo", 4))
		ft_echo();
	else if (!ft_strncmp(cmd->cmd, "exit", 4))
		ft_exit();
	else if (!ft_strncmp(cmd, "export", 6))
	ft_export();

}

void	executor(void)
{
	t_command	*cmd;
	int			keeper;
	char		**paths;
	t_exec		*exec;

	exec = 0;
	exec = malloc (sizeof(t_exec));
	paths = get_paths();
	keeper = 0;
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd || !paths)
		return ;
	if (!cmd->next && is_builtin(*cmd->cmd))
	{
		execute_builtin(cmd);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
	}
	else
	{
		while (cmd)
		{
			if (!is_builtin(*cmd->cmd) && !is_command(cmd, paths))
				ft_printf(2, "%s: command not found\n", *cmd->cmd);
			else
				execute_input(cmd, paths, &keeper);
			if (entry_found("_"))
				update_var("_", *cmd->cmd);
			cmd = cmd->next;
		}
	}

}
