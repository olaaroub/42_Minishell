/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:12:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/18 03:34:27 by hatalhao         ###   ########.fr       */
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

void	ft_exit(t_command *cmd)
{
	unsigned char	status;
	long			arg;

	status = 0;
	if (!cmd->cmd[1])
		return (free_alloc(), exit(status));
	if (cmd->cmd[2])
	{
		g_data.ret_value = 1;
		return (ft_putstr_fd(" too many arguments\n", 2));
	}
	if (all_digits(cmd->cmd[1]))
		arg = ft_atoi(cmd->cmd[1]);
	else
		return (free_alloc(), ft_printf(2, \
		"exit: %s: numeric argument required\n", cmd->cmd[1]), exit(2));
	if (is_integer(arg))
		status = arg;
	else
		status = 2;
	free_alloc();
	exit(status);
}
