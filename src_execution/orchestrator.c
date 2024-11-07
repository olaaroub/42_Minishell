/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/07 16:09:19 by hatalhao         ###   ########.fr       */
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
	
	ft_close(&exec->in);
	ft_close(&exec->tmp_fd);
	ft_close(&exec->out);
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
			exec->pid[i++] = piped_builtin(cmd, exec);
		else
		{
			cmd_path = get_cmd_path(cmd, exec->paths);
			exec->pid[i++] = execute_cmd(cmd_path, cmd, exec);
			free (cmd_path);
		}
		dup2(save_fds[0], 0);// RESET to close cat fd
		dup2(save_fds[1], 1);
		if ((exec->pipefd[0] > 2) && (dup2(exec->pipefd[0], exec->keeper) == -1))
			ft_printf(2, "dup2 in %s: %s\n", __func__, strerror(errno));
		ft_close(&exec->pipefd[0]);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
		cmd = cmd->next;
	}
	i = -1;
	counter = cmd_count();
	while (++i < counter)
		waitpid(exec->pid[i], &g_data.ret_value, 0);
	close(save_fds[0]);
	close(save_fds[1]);
	free (exec->pid);
}

t_exec	*init_exec()
{
	t_exec		*exec;
	t_command	*cmd;
	int			count;

	cmd = g_data.command_list;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	exec = malloc (sizeof(t_exec));
	if (!exec)
		exit(EXIT_FAILURE);
	exec->paths = get_paths();
	if (!exec->paths)
		return (free (exec), exit(EXIT_FAILURE), NULL);
	exec->pid = malloc (sizeof(pid_t) * count);
	exec->in = 0;
	exec->out = 1;
	exec->keeper = 0;
	exec->tmp_fd = -1;
	return (exec);
}

void	executor(void)
{
	t_command	*cmd;
	t_exec		*exec;

	exec = init_exec();
	cmd = g_data.command_list;
	if (!cmd || !cmd->cmd || !*cmd->cmd || !exec->paths)
		return ;
	if (!cmd->next && is_builtin(*cmd->cmd))
	{
		exec->in = STDIN_FILENO;
		exec->out = STDOUT_FILENO;
		execute_builtin(exec, cmd);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
	}
	else
		prepare_input(cmd, exec);
}
