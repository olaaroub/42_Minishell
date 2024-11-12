/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:35:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/12 18:37:53 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valid_option(char *s)
{
	int	i;

	i = 0;
	if (s && s[i] != '-')
		return (0);
	if	(!s[++i])
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_input(char **cmd, int j)
{
	while (j == 0 || (cmd[j] && valid_option(cmd[j])))
		j++;
	while (cmd[j])
	{
		printf("%s", cmd[j++]);
		if (cmd[j])
			printf(" ");
	}
}

void	ft_echo(void)
{
	char	**cmd;
	int		i;
	bool	newline;

	cmd = g_data.command_list->cmd;
	i = 1;
	newline = 1;
	while (cmd[i] && valid_option(cmd[i++]))
		newline = 0;
	print_input(cmd, i - 1);
	if (newline)
		printf("\n");
}
