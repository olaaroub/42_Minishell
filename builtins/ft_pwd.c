/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:57 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/19 08:56:32 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = 0;
	path = getcwd(path, 0);
	if (!path)
	{
		g_data.ret_value = 1;
		return (ft_putendl_fd(strerror(errno), 2));
	}
	printf("%s\n", path);
	g_data.ret_value = 0;
	free(path);
}
