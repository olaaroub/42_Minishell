/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/10/28 19:02:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_heredoc(t_command *cmd)
{
	char	*line;
	char	*name;
	int		fd;

	line = 0;
	name = "/tmp/heredoc_";
	fd = open(name, O_CREAT | O_APPEND, 0644);
	while (true)
	{
		line = get_next_line(0);
		heredoc_signals();
		if (!ft_strcmp(line, cmd->red->file_name))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
	}
	ft_close (fd);
	fd = open (name, O_RDONLY);
	return (fd);
}
