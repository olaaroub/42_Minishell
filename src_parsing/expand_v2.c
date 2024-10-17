/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:46:31 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/17 21:02:32 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    check_master_quotes(bool *double_flag, bool *single_flag, char c)
{
	if(c == '\"' && *double_flag == false && *single_flag == false)
		*double_flag = true;
	else if(c == '\"' && *double_flag == true && *single_flag == false)
		*double_flag = false;
	if(c == '\'' && *single_flag == false && *double_flag == false)
		*single_flag = true;
	else if(c == '\'' && *single_flag == true && *double_flag == false)
		*single_flag = false;


}

int check_env_name(char *buff)
{
	t_env   *tmp;

	tmp = g_data.env_list;
	while(tmp)
	{
		if(!ft_strcmp(buff, tmp->name))
			return(1);
		tmp = tmp->next;
	}
	return -1;

}

int get_expanded(char *buff, int fd)
{
	t_env   *tmp;

	tmp = g_data.env_list;
	while(tmp)
	{
		if(!ft_strcmp(buff, tmp->name))
			return(write(fd, tmp->value, ft_strlen(tmp->value)));
		tmp = tmp->next;
	}
	return 0;
}

static void check_ambiguous(t_tokens *tmp)
{
	char    **check;

	if(!tmp->word || tmp->word[0] == '\0')
	{
		tmp->ambiguous = true;
		// tmp->word = ft_strdup("");
		// g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->word);
	}
	else
	{
		check= split_mgem7a(tmp->word);
		if(check[1] != NULL)
		{
			tmp->ambiguous = true;
			// tmp->word = ft_strdup("");
			// g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->word);
		}
	}
}

int check_special_char(t_tokens *tmp, int *i)
{
	while(tmp->word[*i])
	{
		if(tmp->word[*i] == '$' && tmp->word[*i + 1] == '$')
		{
			(*i) += 2;
			return (*i);
		}
		*i += 1;
	}
	return (*i);
}

int is_special_char(char c)
{
	if(c == '$' || c == '@' || c == '*' || c == '#' || c == '-' || c == '!' || ft_isdigit(c))
		return 1;
	return 0;
}

void    expand(void)
{
	t_tokens   *tmp;
	char *buff;
	int i;
	int start;
	int end;
	int wrote;
	int fd;

	tmp = g_data.token_list;
	while(tmp)
	{
		i = 0;
		fd = open("file.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		wrote = 0;
		while(tmp->word && tmp->word[i])
		{
			check_master_quotes(&g_data.double_flag, &g_data.single_flag, tmp->word[i]);
			if(tmp->word[i] == '$' && ((tmp->prev && tmp->prev->type != HEREDOC) || !tmp->prev) && tmp->word[i+1] != '\0')
			{
				if(is_special_char(tmp->word[i+1]) && ((g_data.double_flag == false && g_data.single_flag == false)
					|| (g_data.double_flag == true )))
					i += 2;
				else if(tmp->word[i+1] =='?' && ((g_data.double_flag == false && g_data.single_flag == false)
					|| (g_data.double_flag == true )))
				{
					ft_putstr_fd(ft_itoa(g_data.ret_value), fd);
					i += 2;
				}
				else// i = check_special_char(tmp, &i);
				{
					start = ++i;
					while(tmp->word[i] && ft_isalnum(tmp->word[i]))
						i++;
					end = i ;
					buff = ft_substr(tmp->word, start, end - start);
					tmp->dollar = ft_strjoin("$", buff);
					g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->dollar);
					if(check_env_name(buff) == 1 && ((g_data.double_flag == false && g_data.single_flag == false)
						|| (g_data.double_flag == true )))
						wrote += get_expanded(buff, fd);
					else if(check_env_name(buff) == 1 && ((g_data.double_flag == false && g_data.single_flag == true)))
					{
						wrote += write(fd, "$", 1);
						wrote += write(fd, buff, ft_strlen(buff));
					}
					else if(check_env_name(buff) == -1 && (g_data.single_flag == true && g_data.double_flag == false))
					{
						wrote += write(fd, "$", 1);
						wrote += write(fd, buff, ft_strlen(buff));
					}
					free(buff);
				}
			}
			else
				wrote += write(fd, &tmp->word[i++], 1);
		}
		close(fd);
		fd = open("file.txt", O_RDONLY);
		tmp->word = get_next_line(fd);
		check_ambiguous(tmp);
		if(tmp->word)
			g_data.trash_list = ft_add_trash(&g_data.trash_list, tmp->word);
		close(fd);
		unlink("file.txt");
		tmp = tmp->next;
	}
}
