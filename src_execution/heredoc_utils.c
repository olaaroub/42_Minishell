/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:43:13 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/13 22:55:57 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	offset_reposition(int fd, char *name)
{
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_printf(2, "heredoc: %s\n", strerror(errno));
	return (fd);
}

char	from_unkonw_to_hex(int x)
{
	char	*hexa;

	if (x < 0)
		x *= -1;
	hexa = "0123456789abcdef";
	return (hexa[x % 16]);
}

char	*create_tmp_file(void)
{
	int		fd;
	char	buffer[10];
	char	result[11];
	int		index;

	index = -1;
	fd = open("/dev/random", O_RDONLY);
	read(fd, buffer, 10);
	buffer[9] = '\0';
	close(fd);
	while (++index < 9)
		result[index] = from_unkonw_to_hex(buffer[index]);
	result[index] = '\0';
	return (ft_strdup(result));
}

int	handle_special_chars2(char *word, int *i, int fd)
{
	if (word[*i + 1] == '"' && g_data.double_flag == true)
		write(fd, &word[(*i)++], 1);
	else if (is_special_char(word[*i + 1]) && ((g_data.double_flag == false
				&& g_data.single_flag == false)
			|| (g_data.double_flag == true)))
		*i += 2;
	else if (word[*i + 1] == '?' && ((g_data.double_flag == false
				&& g_data.single_flag == false)
			|| (g_data.double_flag == true)))
	{
		ft_putstr_fd(ft_itoa(g_data.ret_value), fd);
		*i += 2;
	}
	else
		return (1);
	return (0);
}
