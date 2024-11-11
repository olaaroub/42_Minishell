/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:13 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/11 22:09:38 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// will need to add a cleaning_func();
void	child_proc(t_command *cmd, char *cmd_path, t_exec *exec, char **env)
{
	if (dup2(exec->in, 0) == -1 || dup2(exec->out, 1) == -1)
		ft_printf(2, "dup2 in %s: %s\n", __func__, strerror(errno));
	ft_close(&exec->in);
	ft_close(&exec->out);
	close(exec->pipefd[0]);
	if (execve(cmd_path, cmd->cmd, env) == -1)
	{
		if (0x2 == errno)
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
		else
			ft_printf(2, "execve: %s\n", strerror(errno));
		free_exec(exec);
		exit(1);
	}
}

pid_t	execute_cmd(t_command *cmd, t_exec *exec, char **env)
{
	pid_t	pid;
	char	*cmd_path;

	pid = 0;
	cmd_path = get_cmd_path(cmd, exec->paths);
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child_proc(cmd, cmd_path, exec, env);
	ft_close(&exec->tmp_fd);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[1]);
	free(cmd_path);
	cmd_path = 0;
	return (pid);
}

void	execute_builtin(t_exec *exec, t_command *cmd)
{
	if (cmd->red)
		set_redirections(exec, cmd);
	dup_redirections(exec);
	if (!ft_strcmp(*cmd->cmd, "cd"))
		ft_cd();
	else if (!ft_strcmp(*cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(*cmd->cmd, "env"))
		ft_env();
	else if (!ft_strcmp(*cmd->cmd, "unset"))
		ft_unset();
	else if (!ft_strcmp(*cmd->cmd, "echo"))
		ft_echo();
	else if (!ft_strcmp(*cmd->cmd, "exit"))
		ft_exit();
	else if (!ft_strcmp(*cmd->cmd, "export"))
		ft_export(cmd->cmd);
}

pid_t	piped_builtin(t_command *cmd, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	else if (!pid)
	{
		execute_builtin(exec, cmd);
		exit(g_data.ret_value);
	}
	ft_close(&exec->in);
	ft_close(&exec->tmp_fd);
	ft_close(&exec->out);
	return (pid);
}
