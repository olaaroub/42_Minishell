/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:13 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/26 07:56:13 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error_exit(t_command *cmd, char *cmd_path)
{
	struct stat	unknown;

	stat(cmd_path, &unknown);
	if (!ft_strchr(*cmd->cmd, '/'))
	{
		ft_printf(2, "%s: command not found\n", *cmd->cmd);
		free_alloc();
		exit(127);
	}
	else if (0x2 == errno)
	{
		if (!ft_strchr(*cmd->cmd, '/'))
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
		else
			ft_printf(2, "%s: %s\n", *cmd->cmd, strerror(errno));
		free_alloc();
		exit(127);
	}
	else if (errno == 13 && (unknown.st_mode & __S_IFDIR))
		ft_printf(2, "%s: Is a directory\n", *cmd->cmd);
	else
		ft_printf(2, "%s: %s\n", *cmd->cmd, strerror(errno));
	free_alloc();
	exit(126);
}

void	child_proc(t_command *cmd, char *cmd_path, t_exec *exec, char **env)
{
	dup2(exec->in, 0);
	dup2(exec->out, 1);
	ft_close(&exec->in);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[0]);
	if (execve(cmd_path, cmd->cmd, env) == -1)
		error_exit(cmd, cmd_path);
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
		free_trash(&g_data.trash_list);
		free_env_list();
		exit(0);
	}
	child_proc(cmd, cmd_path, exec, env);
}

pid_t	execute_cmd(t_command *cmd, t_exec *exec, char **env)
{
	pid_t	pid;
	char	*cmd_path;

	pid = 0;
	cmd_path = get_cmd_path(cmd, exec->paths);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, cmd_path);
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child(cmd, exec, env, cmd_path);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[1]);
	// free(cmd_path); it does not get freed if the child proc exited
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
