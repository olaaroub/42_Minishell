/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:27:09 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/20 09:35:34 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_stat(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat) && WTERMSIG(stat) == SIGINT)
		return (1);
	else if (WIFSIGNALED(stat) && WTERMSIG(stat) == SIGQUIT)
		return (131);
	return (1);
}

static void	final(int *save_fds, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	close(save_fds[0]);
	close(save_fds[1]);
	printf("status == %d\n", status);
	g_data.ret_value = exit_stat(status);
}

void	prepare_input(t_command *cmd, t_exec *exec, char **env)
{
	int	save_fds[2];

	save_fds[0] = dup(0);
	save_fds[1] = dup(1);
	while (cmd)
	{
		exec->in = exec->save;
		exec->out = STDOUT_FILENO;
		set_pipes(cmd, exec);
		if (set_redirections(exec, cmd) == -1)
		{
			ft_close(&exec->save);
			ft_close(&exec->pipefd[0]);
			ft_close(&exec->pipefd[1]);
			cmd = cmd->next;
			continue ;
		}
		exec->pid = execute_cmd(cmd, exec, env);
		last_cmd(cmd, exec);
		saving_pipe(cmd, exec);
		dup2(save_fds[0], 0);
		dup2(save_fds[1], 1);
		cmd = cmd->next;
	}
	final(save_fds, exec->pid);
}

t_exec	*init_exec(void)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = malloc(sizeof(t_exec));
	if (!exec)
		exit(EXIT_FAILURE);
	ft_memset(exec, 0, sizeof(t_exec));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec);
	exec->paths = get_paths();
	g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->paths);
	while (exec->paths && exec->paths[i])
		g_data.trash_list = ft_add_trash(&g_data.trash_list, exec->paths[i++]);
	exec->out = 1;
	exec->tmp_fd = -1;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	return (exec);
}

void	executor(char **env)
{
	t_command	*cmd;
	t_exec		*exec;
	int			save_fds[2];

	exec = init_exec();
	cmd = g_data.command_list;
	if (!cmd)
		return ;
	if ((!cmd->cmd || !*cmd->cmd || !**cmd->cmd) \
	&& (cmd->red && cmd->red->type == HEREDOC))
	{
		exec->in = handle_heredoc(cmd);
		return (close(exec->in), unlink(cmd->red->heredoc), (void) NULL);
	}
	if (cmd && is_builtin(*cmd->cmd) && !cmd->next)
	{
		save_fds[0] = dup(0);
		save_fds[1] = dup(1);
		execute_builtin(exec, cmd, 1);
		if (entry_found("_"))
			update_var("_", *cmd->cmd);
		restore_io(save_fds);
	}
	else
		prepare_input(cmd, exec, env);
}
