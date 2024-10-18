/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:52 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/18 13:36:04 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	update_fd(t_command *cmd, t_exec *exec)
{
	if (cmd->red->type == INPUT)
	{
		ft_close(exec->in);
		exec->in = exec->tmp_fd;
	}
	else
	{
		ft_close(exec->out);
		exec->out = exec->tmp_fd;
	}
}

void	set_redirections(t_exec *exec, t_command *cmd)
{
	exec->tmp_fd = -1;
	while (cmd->red)
	{
		if (cmd->red->type == INPUT)
			exec->tmp_fd = open(cmd->red->file_name, O_RDONLY);
		else if (cmd->red->type == OUTPUT)
			exec->tmp_fd = open(cmd->red->file_name, O_CREAT | O_RDWR | O_TRUNC);
		else if (cmd->red->type == APPEND)
			exec->tmp_fd = open(cmd->red->file_name, O_CREAT | O_RDWR | O_APPEND);
		if (exec->tmp_fd == -1)
			return (ft_printf(2, "%s\n", strerror(errno)), ft_close(exec->in), ft_close(exec->out));
		update_fd(cmd, exec);
		cmd->red->next;

	}
}

void	dup_redirections(t_exec *exec)
{
	if (dup2(exec->in, 0) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	if (dup2(exec->out, 1) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	ft_close(exec->in);
	ft_close(exec->out);
}
