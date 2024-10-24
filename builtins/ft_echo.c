/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:35:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/23 07:20:37 by kali             ###   ########.fr       */
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
	bool	newline;

	cmd = g_data.command_list->cmd;
	i = 1;
	j = 0;
	newline = 1;
	while (cmd[i] && valid_option(cmd[i++]))
		newline = 0;
	j += i - (cmd[i] != 0);
	
	while (cmd[j])
	{
		printf("%s", cmd[j++]);
		if (cmd[j])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
