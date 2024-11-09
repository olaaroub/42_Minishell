/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:10 by kali              #+#    #+#             */
/*   Updated: 2024/11/09 22:01:06 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	offset_reposition(int fd, char *name)
{
	close(fd);
	fd = open (name, O_RDONLY);
	if (fd == -1)
		ft_printf(2, "heredoc: %s\n", strerror(errno));
	return (fd);
}

void dollar_expansion(char *word, int *i, int fd)
{
	int	start;
	int	end;
	char *buff;

	if (word[*i + 1] == '"' && g_data.double_flag == true)
		write(fd, &word[(*i)++], 1);
	else if (is_special_char(word[*i + 1]) && ((g_data.double_flag == false && g_data.single_flag == false) || (g_data.double_flag == true)))
		*i += 2;
	else if (word[*i + 1] == '?' && ((g_data.double_flag == false && g_data.single_flag == false) || (g_data.double_flag == true)))
	{
		ft_putstr_fd(ft_itoa(g_data.ret_value), fd);
		*i += 2;
	}
	else
	{
		start = ++(*i);
		if (word[*i] == '_')
			(*i)++;
		while (word[*i] && ft_isalnum(word[*i]))
			(*i)++;
		end = *i;
		buff = ft_substr(word, start, end - start);
		char *dollar = ft_strjoin("$", buff);
		g_data.trash_list = ft_add_trash(&g_data.trash_list, dollar);
		if (check_env_name(buff) == 1 && ((g_data.double_flag == false && g_data.single_flag == false) || (g_data.double_flag == true)))
			get_expanded(buff, fd);
		else if (check_env_name(buff) == 1 && ((g_data.double_flag == false && g_data.single_flag == true)))
		{
			write(fd, "$", 1);
			write(fd, buff, ft_strlen(buff));
		}
		else if (check_env_name(buff) == -1 && (g_data.single_flag == true && g_data.double_flag == false))
		{
			write(fd, "$", 1);
			write(fd, buff, ft_strlen(buff));
		}
		free(buff);
	}
}

char *expand_heredoc(char *word)
{
	int i = 0;
	int fd;
	char *expanded_word;

	fd = open("file2.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (word && word[i])
	{
		check_master_quotes(&g_data.double_flag, &g_data.single_flag, word[i]);
		if (word[i] == '$' && (word[i + 1] != '\0' && !is_whitespace(word[i + 1])))
		{
			dollar_expansion(word, &i, fd);
		}
		else
		{
			write(fd, &word[i++], 1);
		}
	}
	close(fd);
	fd = open("file2.txt", O_RDONLY);
	expanded_word = get_next_line(fd);
	close(fd);
	unlink("file2.txt");
	free(word);
	return expanded_word;
}

void	fill_heredoc(int fd, char *delimiter)
{
	char	*line;

	line = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		line = expand_heredoc(line);
		// printf("line: %s\n", line);
		if (line && !ft_strcmp(line, delimiter))
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
	g_data.trash_list = ft_add_trash(&g_data.trash_list, cmd->red->heredoc);
	fd = open(cmd->red->heredoc, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!pid)
		fill_heredoc(fd, cmd->red->file_name);
	wait(&status);
	return(offset_reposition(fd, cmd->red->heredoc));
}

