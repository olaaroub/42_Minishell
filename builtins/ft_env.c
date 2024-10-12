/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:26:50 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/27 09:43:46 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(void)
{
	t_env	*iter;

	iter = 0;
	iter = g_data.env_list;
	while (iter)
	{
		printf("%s=%s\n", iter->name, iter->value);
		iter = iter->next;
	}
}
