/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/09 22:00:04 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_count(void)
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

void	final_curtain(int *save_fds, t_exec *exec)
{
	int	i;
	int	count;

	i = 0;
	count = cmd_count();
	while (i < count)
		waitpid(exec->pid[i++], &g_data.ret_value, 0);
	close(save_fds[0]);
	close(save_fds[1]);
}

void	prepare_input(t_command *cmd, t_exec *exec, char **env)
{
	int		save_fds[2];
	int 	i;

	i = 0;
	save_fds[0] = dup(0);
	save_fds[1] = dup(1);
	while (cmd)
	{
		exec->in = exec->keeper;
		exec->out = STDOUT_FILENO;
		set_pipes(cmd, exec);
		set_redirections(exec, cmd);
		if (is_builtin(*cmd->cmd))
			exec->pid[i++] = piped_builtin(cmd, exec);
		else
			exec->pid[i++] = execute_cmd(cmd, exec, env);
		dup2(save_fds[0], 0);
		dup2(save_fds[1], 1);
		update(cmd, exec);
		cmd = cmd->next;
	}
	final_curtain(save_fds, exec);
}

t_exec	*init_exec(void)
{
	t_exec		*exec;
	int			count;

	count = cmd_count();
	exec = malloc (sizeof(t_exec));
	if (!exec)
		exit(EXIT_FAILURE);
	exec->paths = get_paths();
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->paths); // add every malloced pointer to trash_list
	if (!exec->paths)
		return (free (exec), exit(EXIT_FAILURE), NULL);
	exec->pid = malloc (sizeof(pid_t) * count);
	exec->in = 0;
	exec->out = 1;
	exec->keeper = 0;
	exec->tmp_fd = -1;
	return (exec);
}

void	executor(char	**env)
{
	t_command	*cmd;
	t_exec		*exec;

	exec = init_exec();
	cmd = g_data.command_list;
	// handle_heredoc(cmd);
	if (!cmd || !cmd->cmd || !*cmd->cmd || !exec->paths)
		return ;
	if (!cmd->next && is_builtin(*cmd->cmd))
	{
		execute_builtin(exec, cmd);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
	}
	else
		prepare_input(cmd, exec, env);
	free_exec(exec);
}
