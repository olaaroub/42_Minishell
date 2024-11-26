/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:28:47 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/26 07:24:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_heredoc(t_redir *red)
{
	int		fd;

	fd = open(red->heredoc, O_RDONLY);
	unlink(red->heredoc);
	return (fd);
}

int	heredoc_present(t_command *cmd)
{
	t_redir	*redir;

	cmd->heredoc = -1;
	while (cmd)
	{
		redir = cmd->red;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				cmd->heredoc = handle_heredoc(redir);
				if (cmd->heredoc == -1)
					return (-1);
				ft_close(&cmd->heredoc);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	check_fd(t_command *cmd, t_exec *exec)
{
	if (exec->tmp_fd == -1)
	{
		if (cmd->red->type == HEREDOC)
		{
			g_data.ret_value = 130;
			return (-1);
		}
		if (cmd->red->type != AMBIG)
			perror(cmd->red->file_name);
		g_data.ret_value = 1;
		return (-1);
	}
	return (0);
}

void	saving_pipe(t_command *cmd, t_exec *exec)
{
	if (!cmd->next)
		return ;
	ft_close(&exec->in);
	exec->save = dup(exec->pipefd[0]);
	ft_close(&exec->pipefd[0]);
}

void	last_cmd(t_command *cmd, t_exec *exec)
{
	if (cmd->next)
		return ;
	ft_close(&exec->in);
	ft_close(&exec->save);
	ft_close(&exec->pipefd[0]);
	ft_close(&exec->pipefd[1]);
	g_data.ret_value = 0;
}
