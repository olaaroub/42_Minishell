/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:52 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/17 05:30:27 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close(int *fd)
{
	if (fd && *fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	update_fd(t_command *cmd, t_exec *exec)
{
	if (cmd->red->type == INPUT || cmd->red->type == HEREDOC)
	{
		ft_close(&exec->in);
		exec->in = exec->tmp_fd;
	}
	else
	{
		ft_close(&exec->out);
		exec->out = exec->tmp_fd;
	}
}

int	set_redirections(t_exec *exec, t_command *cmd)
{
	if (!cmd->red)
		return (-2);
	exec->tmp_fd = -1;
	while (cmd->red)
	{
		if (cmd->red->type == INPUT)
			exec->tmp_fd = open(cmd->red->file_name, O_RDONLY);
		else if (cmd->red->type == OUTPUT)
			exec->tmp_fd = open(cmd->red->file_name, \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (cmd->red->type == APPEND)
			exec->tmp_fd = open(cmd->red->file_name, \
			O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (cmd->red->type == HEREDOC)
			exec->tmp_fd = handle_heredoc(cmd);
		else if (cmd->red->type == AMBIG)
			return (-1);
		if (exec->tmp_fd == -1)
			return (ft_printf(2, " %s\n", strerror(errno)), \
			ft_close(&exec->in), ft_close(&exec->out), -1);
		update_fd(cmd, exec);
		cmd->red = cmd->red->next;
	}
	return (exec->tmp_fd);
}

void	dup_redirections(t_exec *exec)
{
	if (dup2(exec->in, 0) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	if (dup2(exec->out, 1) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	// ft_close(&exec->tmp_fd);
	// ft_close(&exec->in);
	// ft_close(&exec->out);
}

void	set_pipes(t_command *cmd, t_exec *exec)
{
	if (!cmd->next)
		return ;
	if (pipe(exec->pipefd) == -1)
		return (ft_putendl_fd(strerror(errno), 2));
	exec->out = exec->pipefd[1];
}
