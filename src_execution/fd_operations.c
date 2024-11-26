/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:52 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/26 10:38:53 by hatalhao         ###   ########.fr       */
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

void	update_fd(t_redir *red, t_exec *exec)
{
	if (red->type == INPUT || red->type == HEREDOC)
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

int	set_redirections(t_exec *exec, t_redir *red)
{
	if (!red)
		return (-2);
	while (red)
	{
		if (red->file_name && !ft_strcmp(red->file_name, "/dev/stdout"))
		{
			red = red->next;
			continue ;
		}
		if (red->type == INPUT)
			exec->tmp_fd = open(red->file_name, O_RDONLY);
		else if (red->type == OUTPUT)
			exec->tmp_fd = open(red->file_name, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (red->type == APPEND)
			exec->tmp_fd = open(red->file_name, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (red->type == HEREDOC)
			exec->tmp_fd = get_heredoc(red);
		if (check_fd(red, exec) == -1)
			return ((g_data.ret_value = -69), -1);
		update_fd(red, exec);
		red = red->next;
	}
	return (exec->tmp_fd);
}

void	dup_redirections(t_exec *exec)
{
	if (dup2(exec->in, 0) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	if (dup2(exec->out, 1) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	ft_close(&exec->in);
	ft_close(&exec->out);
}

void	set_pipes(t_command *cmd, t_exec *exec)
{
	if (!cmd->next)
		return ;
	if (pipe(exec->pipefd) == -1)
		return (ft_putendl_fd(strerror(errno), 2));
	exec->out = exec->pipefd[1];
}
