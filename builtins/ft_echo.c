/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:35:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/19 08:56:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	valid_option(char *s)
{
	int	i;

	i = 0;
	if (s && s[i] != '-')
		return (0);
	if (!s[++i])
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
		ft_printf(1, "%s", cmd[j++]);
		if (cmd[j])
			ft_printf(1, " ");
	}
}

void	ft_echo(t_command *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = 1;
	while (cmd->cmd[i] && valid_option(cmd->cmd[i++]))
		newline = 0;
	print_input(cmd->cmd, i - 1);
	if (newline)
		ft_printf(1, "\n");
	g_data.ret_value = 0;
}
