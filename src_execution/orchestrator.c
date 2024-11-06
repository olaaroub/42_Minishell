/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/06 17:59:16 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_count()
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = g_data.command_list;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

pid_t	piped_builtin(t_command *cmd, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_printf(2, "fork: %s\n", strerror(errno));
	else if (!pid)
		execute_builtin(exec, cmd);
	else
	{
		ft_close(&exec->in);
		ft_close(&exec->tmp_fd);
		ft_close(&exec->out);
	}
	return (pid);
}

void	prepare_input(t_command *cmd, t_exec *exec)
{
	char	*cmd_path;
	int		i;
	int		counter;
	int		save_fds[2];

	counter = 0;
	i = 0;
	cmd_path = 0;
	save_fds[0] = dup(0);
	save_fds[1] = dup(1);
	while (cmd)
	{
		exec->in = exec->keeper; // 0
		exec->out = STDOUT_FILENO; // 1
		set_pipes(cmd, exec);
		set_redirections(exec, cmd);
		if (is_builtin(*cmd->cmd))
			piped_builtin(cmd, exec);
		else
		{
			cmd_path = get_cmd_path(cmd, exec->paths);
			exec->pid[i++] = execute_cmd(cmd_path, cmd, exec);
			free (cmd_path);
		}
		dup2(save_fds[0], 0);// RESET to close cat fd
		dup2(save_fds[1], 1);
		if ((exec->pipefd[0] > 2) && (dup2(exec->pipefd[0], exec->keeper) == -1))
			ft_printf(2, "dup2: %s\n", strerror(errno));
		ft_close(&exec->pipefd[0]);
		cmd = cmd->next;
	}
	i = -1;
	counter = cmd_count();
	while (++i < counter)
		waitpid(exec->pid[i], &g_data.ret_value, 0);
	close(save_fds[0]);
	close(save_fds[1]);
}

void	command_chain(t_command *cmd, t_exec *exec)
{
	if (!is_builtin(*cmd->cmd) && !is_command(cmd, exec->paths))
		ft_printf(2, "%s: command not found\n", *cmd->cmd);
	else
		prepare_input(cmd, exec);
	if (entry_found("_"))
		update_var("_", *cmd->cmd);
}

void	executor(void)
{
	t_command	*cmd;
	t_exec		*exec;

	exec = 0;
	exec = malloc (sizeof(t_exec));
	exec->paths = get_paths();
	exec->pid = malloc (sizeof(pid_t) * cmd_count());
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
		command_chain(cmd, exec);
}
