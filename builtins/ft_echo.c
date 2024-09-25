/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:35:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/25 11:34:22 by hatalhao         ###   ########.fr       */
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

void	ft_echo(void)
{
	char	**cmd;
	int		i;
	int		j;
	bool	nl;

	cmd = g_data.command_list->cmd;
	i = 1;
	j = 0;
	nl = 1;
	while (cmd[i])
	{	
		if (valid_option(cmd[i++]))
			nl = 0;
		else
			break ;
	}
	j += i - (cmd[1] != 0);
	while (cmd[j])
	{
		printf("%s", cmd[j++]);
		if (nl)
			printf("\n");
	}
}
