/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:50 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/23 06:52:44 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(void)
{
	t_env	*iter;

	iter = g_data.env_list;
	while (iter)
	{
		printf("%s=%s\n", iter->name, iter->value);
		iter = iter->next;
	}
}
