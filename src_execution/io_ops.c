/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:40:49 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/19 01:24:16 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	restore_io(int *saved)
{
	dup2(saved[0], 0);
	dup2(saved[1], 1);
	close(saved[0]);
	close(saved[1]);
}

void	mod_fds(t_exec *exec)
{
	ft_close(&exec->save);
	ft_close(&exec->in);
	exec->save = dup(exec->pipefd[0]);
	ft_close(&exec->out);
	ft_close(&exec->pipefd[0]);
	ft_close(&exec->pipefd[1]);
}
