/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:35:17 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/08 09:41:33 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
		free(arr[i++]);
	arr = 0;
}

void    free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	free_arr(exec->paths);
	free(exec->pid);
	free(exec);
}
