/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:13 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/17 23:51:19 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// will need to add a cleaning_func();
void	child_proc(t_command *cmd, char *cmd_path, t_exec *exec, char **env)
{
	dup2(exec->in, 0);
	dup2(exec->out, 1);
	ft_close(&exec->in);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[0]);
	if (execve(cmd_path, cmd->cmd, env) == -1)
	{
		if (0x2 == errno)
		{
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
			exit(127);
		}
		else
			ft_printf(2, "%s: %s\n", *cmd->cmd, strerror(errno));
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
	{
		ft_close(&exec->pipefd[0]);
		if (is_builtin(*cmd->cmd))
		{
			ft_close(&exec->in);
			exec->in = 0;
			execute_builtin(exec, cmd, 0);
			exit(g_data.ret_value);
		}
		else if (cmd_path == NULL)
		{
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
			free_trash(&g_data.trash_list);
			free_env_list();
			exit (127);
		}
		else
			child_proc(cmd, cmd_path, exec, env);
	}
	ft_close(&exec->out);
	ft_close(&exec->pipefd[1]);
	free(cmd_path);
	cmd_path = 0;
	return (pid);
}

void	execute_builtin(t_exec *exec, t_command *cmd, int flag)
{
	if (flag == 1)
	{
		if (cmd->red)
			if (set_redirections(exec, cmd) == -1)
				return ;
	}
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
		ft_echo(cmd);
	else if (!ft_strcmp(*cmd->cmd, "exit"))
		ft_exit();
	else if (!ft_strcmp(*cmd->cmd, "export"))
		g_data.ret_value = ft_export(cmd->cmd);
}

// void	piped_builtin(t_command *cmd, t_exec *exec)
// {
	// pid_t	pid;

	// pid = fork();
	// if (pid == -1)
	// 	ft_printf(2, "fork: %s\n", strerror(errno));
	// else if (!pid)
	// {
		
	// }
	// ft_close(&exec->in);
	// ft_close(&exec->tmp_fd);
	// ft_close(&exec->out);
	// ft_close(&exec->pipefd[1]);
	// return (pid);
// }
