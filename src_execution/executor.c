/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/18 13:35:09 by hatalhao         ###   ########.fr       */
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
	int	pid;
	int	pipefd[2];
	int	in;
	int	out;

	
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

void	execute_input(t_command *cmd, t_exec *exec)
{
	char	*cmd_path;

	cmd_path = 0;
	while (cmd)
	{
		if (cmd->red)
			set_redirections(exec, cmd);
		execute_cmd(cmd_path, cmd, exec->keeper);
		cmd = cmd->next;
	}
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
	// else if (!ft_strncmp(cmd, "export", 6))
	// 	return (1);
	return (0);
}

void	execute_builtin(t_exec *exec, t_command *cmd)
{
	int	in_fd;
	int	out_fd;

	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	if (cmd->red)
		set_redirections(exec, cmd);
	dup_redirections(exec);
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
	// else if (!ft_strncmp(cmd, "export", 6))
	// 	ft_export();
}

void	executor(void)
{
	t_command	*cmd;
	t_exec		*exec;

	exec = 0;
	exec = malloc (sizeof(t_exec));
	exec->paths = get_paths();
	exec->keeper = 0;
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd || !exec->paths)
		return ;
	if (!cmd->next && is_builtin(*cmd->cmd))
	{
		execute_builtin(exec, cmd);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
	}
	else
	{
		while (cmd)
		{
			if (!is_builtin(*cmd->cmd) && !is_command(cmd, exec->paths))
				ft_printf(2, "%s: command not found\n", *cmd->cmd);
			else
				execute_input(cmd, exec);
			if (entry_found("_"))
				update_var("_", *cmd->cmd);
			cmd = cmd->next;
		}
	}
}
