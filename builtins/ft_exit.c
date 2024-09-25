/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:12:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 15:48:16 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_integer(long nb)
{
		return (nb >= INT_MIN && nb <= INT_MAX);
}

void    ft_exit(void)
{
		unsigned char   status;
		long                    arg;

		arg = ft_atoi(g_data.command_list->cmd[1]);
		status = 0;
		if (g_data.command_list->cmd[2])
		{
				ft_putstr_fd("too many arguements\n", 2);
				return ;
		}
		if (is_integer(arg))
				status = arg;
		else
				status = 2;
		exit(status);
}
