/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/11/07 16:02:45 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	heredoc_signals()
// {
// 	// signal(SIGINT, SIG_IGN);
// 	// signal(SIGQUIT, SIG_IGN);
// }

int	handle_heredoc(t_command *cmd)
{
	char	*line;
	char	*name;
	char	*delimiter;
	int		fd;

	line = 0;
	name = "/tmp/heredoc_";
	delimiter = cmd->red->file_name;
	fd = open(name, O_CREAT | O_APPEND, 0644);
	while (true)
	{
		line = readline("");
		// heredoc_signals();
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	ft_close(&fd);
	fd = open (name, O_RDONLY);
	return (fd);
}
