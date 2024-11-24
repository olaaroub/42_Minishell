/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/11/24 09:34:23 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	dollar_expansion(char *word, int *i, int fd)
{
	int		start;
	int		end;
	char	*buff;

	if (handle_special_chars2(word, i, fd) == 0)
		return ;
	else
	{
		start = ++(*i);
		if (word[*i] == '_')
			(*i)++;
		while (word[*i] && ft_isalnum(word[*i]))
			(*i)++;
		end = *i;
		buff = ft_substr(word, start, end - start);
		start_expand(buff, fd);
		free(buff);
	}
}

static char	*expand_heredoc(char *word, char *delimiter)
{
	int		i;
	int		fd;
	char	*expanded_word;

	i = 0;
	if (!ft_strcmp(word, delimiter))
		return (word);
	fd = open("file2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (word && word[i])
	{
		check_master_quotes(&g_data.double_flag, &g_data.single_flag, word[i]);
		if (word[i] == '$' && (word[i + 1] != '\0' && !is_whitespace(word[i
						+ 1])))
			dollar_expansion(word, &i, fd);
		else
			write(fd, &word[i++], 1);
	}
	close(fd);
	fd = open("file2.txt", O_RDONLY);
	expanded_word = get_next_line(fd);
	close(fd);
	unlink("file2.txt");
	free(word);
	return (expanded_word);
}

void	sigheredoc(int sig)
{
	(void)sig;
	ft_putendl_fd("^C", 1);
	exit(130);
}

void	fill_heredoc(int fd, char *delimiter)
{
	char	*line;

	line = 0;
	signal(SIGINT, sigheredoc);
	while (true)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		line = expand_heredoc(line, delimiter);
		if (line && !ft_strcmp(line, delimiter))
			return (free_env_list(), free(line), \
			free_trash(&g_data.trash_list), exit(0));
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(t_redir *red)
{
	int		status;
	int		fd;
	int		pid;
	char	*tmp;

	tmp = create_tmp_file();
	red->heredoc = ft_strjoin("/tmp/heredoc/", tmp);
	free(tmp);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, red->heredoc);
	fd = open(red->heredoc, O_CREAT | O_WRONLY | O_APPEND, 0644);
	pid = fork();
	if (!pid)
		fill_heredoc(fd, red->file_name);
	wait(&status);
	g_data.ret_value = exit_stat(status);
	if (g_data.ret_value == 130)
		return (close(fd), unlink(red->heredoc), -1);
	return (offset_reposition(fd, red->heredoc));
}
