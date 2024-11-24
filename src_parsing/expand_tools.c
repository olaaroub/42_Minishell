/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:38:07 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/20 19:08:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_master_quotes(bool *double_flag, bool *single_flag, char c)
{
	if (c == '\"' && *double_flag == false && *single_flag == false)
		*double_flag = true;
	else if (c == '\"' && *double_flag == true && *single_flag == false)
		*double_flag = false;
	if (c == '\'' && *single_flag == false && *double_flag == false)
		*single_flag = true;
	else if (c == '\'' && *single_flag == true && *double_flag == false)
		*single_flag = false;
}

int	check_env_name(char *buff)
{
	t_env	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		if (!ft_strcmp(buff, tmp->name))
			return (1);
		tmp = tmp->next;
	}
	return (-1);
}

int	get_expanded(char *buff, int fd)
{
	t_env	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		if (!ft_strcmp(buff, tmp->name))
			return (write(fd, tmp->value, ft_strlen(tmp->value)));
		tmp = tmp->next;
	}
	return (0);
}

void	start_expand(char *buff, int fd)
{
	if (check_env_name(buff) == 1 && ((g_data.double_flag == false
				&& g_data.single_flag == false)
			|| (g_data.double_flag == true)))
		get_expanded(buff, fd);
	else if (check_env_name(buff) == 1 && ((g_data.double_flag == false
				&& g_data.single_flag == true)))
	{
		write(fd, "$", 1);
		write(fd, buff, ft_strlen(buff));
	}
	else if (check_env_name(buff) == -1 && (g_data.single_flag == true
			&& g_data.double_flag == false))
	{
		write(fd, "$", 1);
		write(fd, buff, ft_strlen(buff));
	}
}

char	*get_filename(void)
{
	char	*filename;
	char	rand[6];
	int		tmp_fd;

	tmp_fd = open("/dev/urandom", O_RDONLY);
	read(tmp_fd, rand, 5);
	rand[5] = '\0';
	close(tmp_fd);
	filename = ft_strjoin("/tmp/", rand);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, filename);
	return (filename);
}
