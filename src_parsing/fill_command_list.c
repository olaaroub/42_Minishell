/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:24:13 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/26 17:55:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*trim_quotes(char *word)
{
	char	*ret;
	char	quote;

	g_data.i = 0;
	g_data.j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!word || !ret)
		return (NULL);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, ret);
	while (word[g_data.i])
	{
		if (word[g_data.i] == '"' || word[g_data.i] == '\'')
		{
			quote = word[g_data.i++];
			while (word[g_data.i] && word[g_data.i] != quote)
				ret[g_data.j++] = word[g_data.i++];
			if (word[g_data.i] == quote)
				g_data.i++;
		}
		else
			ret[g_data.j++] = word[g_data.i++];
	}
	ret[g_data.j] = '\0';
	return (ret);
}

static int	handle_redirs(t_tokens **temp, t_redir **redir, char **commands,
		int *i)
{
	if ((*temp)->type == HEREDOC)
	{
		*redir = ft_add_redir(redir, (*temp)->next->word, HEREDOC);
		if (!*redir)
			return (MALLOC_ERROR);
	}
	else if ((*temp)->next && (*temp)->next->ambiguous == false)
	{
		*redir = ft_add_redir(redir, trim_quotes((*temp)->next->word),
				(*temp)->type);
		if (!*redir)
			return (MALLOC_ERROR);
	}
	else if ((*temp)->next)
	{
		if (handle_ambiguous(temp, redir, commands, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		return (-1);
	}
	(*temp) = (*temp)->next->next;
	return (0);
}

static int	handle_command(t_tokens **temp, char **commands, int *i)
{
	int	j;

	j = 0;
	if ((*temp)->word_after_exp && (*temp)->word_after_exp[1] != NULL)
	{
		while ((*temp)->word_after_exp[j])
		{
			commands[*i] = ft_strdup(trim_quotes((*temp)->word_after_exp[j++]));
			if (!commands[*i])
				return (MALLOC_ERROR);
			g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[*i]);
			(*i)++;
		}
	}
	else if ((*temp)->word)
	{
		(*temp)->word = trim_quotes((*temp)->word);
		commands[*i] = ft_strdup((*temp)->word);
		if (!commands[*i])
			return (MALLOC_ERROR);
		g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[*i]);
		(*i)++;
	}
	(*temp) = (*temp)->next;
	return (0);
}

static int	fill_commands_redirs(t_tokens **temp, t_redir **redir,
		char **commands)
{
	int	i;

	i = 0;
	*redir = NULL;
	while (*temp && (*temp)->type != PIPE)
	{
		if ((*temp)->type == INPUT || (*temp)->type == OUTPUT
			|| (*temp)->type == APPEND || (*temp)->type == HEREDOC)
		{
			if (handle_redirs(temp, redir, commands, &i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		else
		{
			if (handle_command(temp, commands, &i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
	}
	commands[i] = 0;
	return (0);
}

int	fill_command_list(void)
{
	t_tokens	*temp;
	t_redir		*redir;
	char		**commands;
	int			len;

	if (expand() == MALLOC_ERROR || split_tokens() == MALLOC_ERROR)
		return (free_trash(&g_data.trash_list), MALLOC_ERROR);
	temp = g_data.token_list;
	while (temp)
	{
		len = len_until_pipe(temp);
		commands = (char **)malloc(sizeof(char *) * (len + 1));
		if (!commands)
			return (free_trash(&g_data.trash_list), MALLOC_ERROR);
		g_data.trash_list = ft_add_trash(&g_data.trash_list, commands);
		if (fill_commands_redirs(&temp, &redir, commands) == MALLOC_ERROR)
			return (free_trash(&g_data.trash_list), MALLOC_ERROR);
		g_data.command_list = ft_add_command(&g_data.command_list, commands,
				redir);
		if (!g_data.command_list)
			return (free_trash(&g_data.trash_list), MALLOC_ERROR);
		if (temp)
			temp = temp->next;
	}
	return (0);
}
