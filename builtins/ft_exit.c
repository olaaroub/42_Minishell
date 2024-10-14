/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:12:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/10 09:29:37 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	arg = ft_atoi(g_data.command_list->cmd[1]);
	if (g_data.command_list->cmd[2])
		return ft_putstr_fd("too many arguements\n", 2);
	if (is_integer(arg))
		status = arg;
	else
		status = 2;
	// Will need to free the line and the env list here
	exit(status);
}
