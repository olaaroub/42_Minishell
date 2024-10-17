/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:52 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/10 10:27:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	update_fd(t_command *cmd, int *in, int *out, int tmp)
{
	if (cmd->red->type == INPUT)
	{
		ft_close(*in);
		*in = tmp;
	}
	else
	{
		ft_close(*out);
		*out = tmp;
	}
}

void	set_redirections(int *in, int *out, t_command *cmd)
{
	int	tmp;

	tmp = -1;
	while (cmd->red)
	{
		if (cmd->red->type == INPUT)
			tmp = open(cmd->red->file_name, O_RDONLY);
		else if (cmd->red->type == OUTPUT)
			tmp = open(cmd->red->file_name, O_CREAT | O_RDWR | O_TRUNC);
		else if (cmd->red->type == APPEND)
			tmp = open(cmd->red->file_name, O_CREAT | O_RDWR | O_APPEND);
		// HEREDOC is an exception here;
		if (tmp == -1)
			return (ft_printf(2, "%s\n", strerror(errno)), ft_close(*in), ft_close(*out));
		update_fd(cmd, in, out, tmp);
		cmd->red->next;
	}
}

void	dup_redirections(int in, int out)
{
	if (dup2(in, 0) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	if (dup2(out, 1) == -1)
		ft_printf(2, "%s\n", strerror(errno));
	ft_close(in);
	ft_close(out);
}
