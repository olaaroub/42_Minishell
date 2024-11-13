/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:12:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/11 20:48:48 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	all_digits(char *str)
{
	int	i;

	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_integer(long nb)
{
	return (nb >= INT_MIN && nb <= INT_MAX);
}

void	ft_exit(void)
{
	unsigned char	status;
	long			arg;
	char			**cmd;

	cmd = g_data.command_list->cmd;
	status = 0;
	if (!cmd[1])
		exit(status);
	if (cmd[2])
	{
		g_data.ret_value = 1;
		return (ft_putstr_fd(" too many arguments\n", 2));
	}
	if (all_digits(cmd[1]))
		arg = ft_atoi(cmd[1]);
	else
		return (ft_printf(2, \
		"exit: %s: numeric argument required\n", cmd[1]), exit(2));
	if (is_integer(arg))
		status = arg;
	else
		status = 2;
	free_trash(&g_data.trash_list);
	exit(status);
}
