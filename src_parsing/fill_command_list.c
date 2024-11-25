/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:24:13 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/25 16:58:41 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*trim_quotes(char *word)
{
	char	*ret;
	char	quote;

	g_data.i = 0;
	g_data.j = 0;
	if (!word)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(word) + 1));
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
	if ((*temp)->next && (*temp)->next->ambiguous == false)
		*redir = ft_add_redir(redir, trim_quotes((*temp)->next->word),
				(*temp)->type);
	else if ((*temp)->next)
	{
		ft_printf(2, "minishell: %s: AMBIGUOUS REDIRECT\n",
			(*temp)->next->dollar);
		g_data.ret_value = 1;
		*redir = ft_add_redir(redir, NULL, AMBIG);
		commands[*i] = NULL;
		while ((*temp) && (*temp)->type != PIPE)
			(*temp) = (*temp)->next;
		return (-1);
	}
	(*temp) = (*temp)->next->next;
	return (0);
}

static void	handle_command(t_tokens **temp, char **commands, int *i)
{
	int	j;

	j = 0;
	if ((*temp)->word_after_exp && (*temp)->word_after_exp[1] != NULL)
	{
		while ((*temp)->word_after_exp[j])
		{
			commands[*i] = ft_strdup(trim_quotes((*temp)->word_after_exp[j++]));
			g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[*i]);
			(*i)++;
		}
	}
	else if ((*temp)->word)
	{
		(*temp)->word = trim_quotes((*temp)->word);
		commands[*i] = ft_strdup((*temp)->word);
		g_data.trash_list = ft_add_trash(&g_data.trash_list, commands[*i]);
		(*i)++;
	}
	(*temp) = (*temp)->next;
}

static void	fill_commands_redirs(t_tokens **temp, t_redir **redir,
		char **commands)
{
	int	i;

	i = 0;
	while (*temp && (*temp)->type != PIPE)
	{
		if ((*temp)->type == INPUT || (*temp)->type == OUTPUT
			|| (*temp)->type == APPEND || (*temp)->type == HEREDOC)
		{
			if (handle_redirs(temp, redir, commands, &i) == -1)
				return ;
		}
		else
			handle_command(temp, commands, &i);
	}
	commands[i] = 0;
	return ;
}

void	fill_command_list(void)
{
	t_tokens	*temp;
	t_redir		*redir;
	char		**commands;
	int			len;

	expand();
	split_tokens();
	temp = g_data.token_list;
	while (temp)
	{
		len = len_until_pipe(temp);
		commands = (char **)malloc(sizeof(char *) * (len + 1));
		g_data.trash_list = ft_add_trash(&g_data.trash_list, commands);
		redir = NULL;
		fill_commands_redirs(&temp, &redir, commands);
		g_data.command_list = ft_add_command(&g_data.command_list, commands,
				redir);
		if (temp)
			temp = temp->next;
	}
}
