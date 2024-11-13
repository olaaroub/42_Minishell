/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/13 06:52:11 by hatalhao         ###   ########.fr       */
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
	if (WIFEXITED(g_data.ret_value))
		g_data.ret_value = WEXITSTATUS(g_data.ret_value);
	else if (WIFSIGNALED(g_data.ret_value))
		g_data.ret_value = WTERMSIG(g_data.ret_value) + 128;
	close(save_fds[0]);
	close(save_fds[1]);
}

void	prepare_input(t_command *cmd, t_exec *exec, char **env)
{
	int		save_fds[2];
	int		i;

	i = 0;
	save_fds[0] = dup(0);
	save_fds[1] = dup(1);
	while (cmd)
	{
		exec->in = exec->keeper;
		exec->out = STDOUT_FILENO;
		set_pipes(cmd, exec);
		if (set_redirections(exec, cmd) == -1)
			return ;
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
	int			i;

	i = 0;
	count = cmd_count();
	exec = malloc (sizeof(t_exec));
	if (!exec)
		exit(EXIT_FAILURE);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec);
	exec->paths = get_paths();
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->paths);
	while (exec->paths && exec->paths[i])
		g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->paths[i++]);
	exec->pid = malloc (sizeof(pid_t) * count);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->pid);
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
	int			save_fds[2];

	if(!g_data.command_list || !g_data.command_list->cmd || !*g_data.command_list->cmd)
		return ; // without this check, the program displays (null): Bad address when entering smtn like $C
	exec = init_exec();
	cmd = g_data.command_list;
	if (cmd && is_builtin(*cmd->cmd) && !cmd->next)
	{
		save_fds[0] = dup(0);
		save_fds[1] = dup(1);
		execute_builtin(exec, cmd, 0);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
		restore_io(save_fds);
	}
	else
		prepare_input(cmd, exec, env);
}
