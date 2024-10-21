/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:13 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/19 20:07:59 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_proc(t_command *cmd, char *cmd_path, t_exec *exec)
{
	printf("in == %d\t	out == %d\n", exec->in, exec->out);
	if (dup2(exec->in, 0) == -1 || dup2(exec->out, 1) == -1)
		ft_printf(2, "dup2: %s\n", strerror(errno));
	ft_close(exec->in);
	if (cmd->next)
		ft_close(exec->out);
	if (execve(cmd_path, cmd->cmd, NULL) == -1)
	{
		ft_printf(2, "execve: %s\n", strerror(errno));	
		exit(1);
	}
}

int	execute_cmd(char *cmd_path, t_command *cmd, t_exec *exec)
{
	int	pid;

	pid = 0;
	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	if (pid == 0)
		child_proc(cmd, cmd_path, exec);
	else
	{
		ft_close(exec->in);
		ft_close(exec->out);
		if (cmd->next && !cmd->red)
			exec->keeper = exec->pipefd[0];
	}
	return (pid);
}

void	execute_builtin(t_exec *exec, t_command *cmd)
{
	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
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
