/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:45 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 09:26:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(void)
{
	char	*path;

	if (!g_data.command_list->cmd[1])
		return ;
	path = g_data.command_list->cmd[1];
	if (chdir(path) == -1)
		ft_putstr_fd(strerror(errno), 2);
}
