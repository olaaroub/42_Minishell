/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/19 20:32:58 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	command_chain(t_command *cmd, t_exec *exec)
{
	while (cmd)
	{
		if (!is_builtin(*cmd->cmd) && !is_command(cmd, exec->paths))
			ft_printf(2, "%s: command not found\n", *cmd->cmd);
		else
			prepare_input(cmd, exec);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
		cmd = cmd->next;
	}
}

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

void	prepare_input(t_command *cmd, t_exec *exec)
{
	char	*cmd_path;
	int		i;
	int		counter;

	counter = 0;
	i = 0;
	cmd_path = 0;
	cmd_path = get_cmd_path(cmd, exec->paths);
	while (cmd)
	{
		exec->in = 0;
		exec->out = 1;
		if (cmd->red)
			set_redirections(exec, cmd);
		exec->pid[i++] = execute_cmd(cmd_path, cmd, exec);
		cmd = cmd->next;
	}
	i = -1;
	counter = cmd_count();
	while (++i < cmd_count())
		waitpid(exec->pid[i], NULL, 0);
}

void	executor(void)
{
	t_command	*cmd;
	t_exec		*exec;

	exec = 0;
	exec = malloc (sizeof(t_exec));
	exec->paths = get_paths();
	exec->pid = malloc (sizeof(int) * cmd_count());
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
