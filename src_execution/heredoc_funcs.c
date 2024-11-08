/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/11/08 11:40:36 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	heredoc_signals(void)
// {
	
// }

int	offset_reposition(int fd, char *name)
{
	close(fd);
	fd = open (name, O_RDONLY);
	if (fd == -1)
		ft_printf(2, "heredoc: %s\n", strerror(errno));
	return (fd);
}

void	fill_heredoc(int fd, char *delimiter)
{
	char	*line;

	line = 0;
	while (true)
	{
		line = readline("> ");
		// heredoc_signals();
		if (!line)
			exit(0);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(t_command *cmd)
{
	int 	status;
	int		fd;
	int		pid;

	pid = fork();
	cmd->red->heredoc = ft_strdup("/tmp/heredoc_");
	fd = open(cmd->red->heredoc, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!pid)
		fill_heredoc(fd, cmd->red->file_name);
	wait(&status);
	return(offset_reposition(fd, cmd->red->heredoc));
}

