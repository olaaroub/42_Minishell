/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/11/08 09:22:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	print_file_content(int fd)
{
	char	*line;

	line = 0;
	printf("Printing file content\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_putendl_fd(line, 1);
		free(line);
	}
	// ft_close(&fd);
}

void	fill_heredoc(int fd, char *delimiter)
{
	char	*line;

	line = 0;
		while (true)
		{
			line = readline("> ");
			if (!line)
				exit(0);
			heredoc_signals();
			if (!ft_strcmp(line, delimiter))
			{
				free(line);
				exit(0);
			}
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
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
	close(fd);
	fd = open (cmd->red->heredoc, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "heredoc: %s\n", strerror(errno));
		return (-1);
	}
	return (fd);
}

