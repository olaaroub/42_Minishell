/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:13 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/24 09:42:27 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			// ft_printf(2, "%s: command not found\n", *cmd->cmd);
			perror("execve");
			exit(127);
		}
		else
			ft_printf(2, "%s: %s\n", *cmd->cmd, strerror(errno));
			// perror("execve");
		free_exec(exec);
		exit(126);
	}
}

void	child(t_command *cmd, t_exec *exec, char **env, char *cmd_path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
		if (*cmd->cmd)
		{
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
			g_data.ret_value = 127;
		}
		free_trash(&g_data.trash_list);
		free_env_list();
		exit(g_data.ret_value);
	}
	child_proc(cmd, cmd_path, exec, env);
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
		child(cmd, exec, env, cmd_path);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[1]);
	free(cmd_path);
	cmd_path = 0;
	return (pid);
}

void	execute_builtin(t_exec *exec, t_command *cmd, int flag)
{
	if (flag == 1 && cmd->red)
		if (set_redirections(exec, cmd) == -1)
			return ;
	dup_redirections(exec);
	if (!ft_strcmp(*cmd->cmd, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(*cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(*cmd->cmd, "env"))
		ft_env();
	else if (!ft_strcmp(*cmd->cmd, "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(*cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(*cmd->cmd, "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(*cmd->cmd, "export"))
		g_data.ret_value = ft_export(cmd->cmd);
}
