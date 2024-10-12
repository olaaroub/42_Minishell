/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:57 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 09:26:58 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char 	*path;

	path = 0;
	path = getcwd(path, 0);
	if (!path)
		return (ft_putstr_fd(strerror(errno), 2));
	printf("%s\n", path);
	free(path);
}
