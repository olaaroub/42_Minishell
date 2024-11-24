/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:46:31 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/20 19:08:32 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	check_ambiguous(t_tokens *tmp)
{
	char	**check;

	if (!tmp->word || tmp->word[0] == '\0')
		tmp->ambiguous = true;
	else
	{
		check = customized_split(tmp->word);
		if (check[1] != NULL)
			tmp->ambiguous = true;
	}
}

static int	handle_special_chars(t_tokens *tmp, int *i, int fd)
{
	if (tmp->word[*i + 1] == '"' && g_data.double_flag == true)
		write(fd, &tmp->word[(*i)++], 1);
	else if (is_special_char(tmp->word[*i + 1]) && ((g_data.double_flag == false
				&& g_data.single_flag == false)
			|| (g_data.double_flag == true)))
		*i += 2;
	else if (tmp->word[*i + 1] == '?' && ((g_data.double_flag == false
				&& g_data.single_flag == false)
			|| (g_data.double_flag == true)))
	{
		ft_putnbr_fd(g_data.ret_value, fd);
		*i += 2;
	}
	else
		return (1);
	return (0);
}

static void	prepare_expand(t_tokens *tmp, int *i, int fd)
{
	int		start;
	int		end;
	char	*buff;

	if (handle_special_chars(tmp, i, fd) == 0)
		return ;
	else
	{
		start = ++*i;
		if (tmp->word[*i] == '_')
			*i += 1;
		while (tmp->word[*i] && ft_isalnum(tmp->word[*i]))
			*i += 1;
		end = *i;
		buff = ft_substr(tmp->word, start, end - start);
		tmp->dollar = ft_strjoin("$", buff);
		g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->dollar);
		start_expand(buff, fd);
		free(buff);
	}
}

static void	process_tokens(t_tokens *tmp, int fd)
{
	int	i;

	i = 0;
	while (tmp->word && tmp->word[i])
	{
		check_master_quotes(&g_data.double_flag, &g_data.single_flag,
			tmp->word[i]);
		if (tmp->word[i] == '$' && ((tmp->prev && tmp->prev->type != HEREDOC)
				|| !tmp->prev) && (tmp->word[i + 1] != '\0'
				&& !is_whitespace(tmp->word[i + 1])))
			prepare_expand(tmp, &i, fd);
		else
			write(fd, &tmp->word[i++], 1);
	}
}

void	expand(void)
{
	t_tokens	*tmp;
	int			fd;
	char		*filename;

	tmp = g_data.token_list;
	filename = create_tmp_file();
	ft_add_trash(&g_data.trash_list, filename);
	while (tmp)
	{
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		process_tokens(tmp, fd);
		close(fd);
		fd = open(filename, O_RDONLY);
		tmp->word = get_next_line(fd);
		check_ambiguous(tmp);
		if (tmp->word)
			g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->word);
		close(fd);
		unlink(filename);
		tmp = tmp->next;
	}
}
