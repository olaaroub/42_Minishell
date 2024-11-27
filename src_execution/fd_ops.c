/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 06:45:02 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/27 06:45:03 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_counter(t_command *cmd)
{
	int		counter;
	t_redir	*redir;

	counter = 0;
	while (cmd)
	{
		redir = cmd->red;
		while (redir)
		{
			if (redir->type == HEREDOC)
				counter++;
			if (counter > 16)
			{
				ft_printf(2, \
				"minishell: maximum here-document count exceeded\n");
				free_alloc();
				exit(2);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	open_file(t_redir *red, int type)
{
	int	fd;

	fd = -1;
	if (type == INPUT)
		fd = open(red->file_name, O_RDONLY);
	else if (type == OUTPUT)
		fd = open(red->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(red->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == HEREDOC)
		fd = get_heredoc(red);
	return (fd);
}
