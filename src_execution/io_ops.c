/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:40:49 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/14 07:14:21 by hatalhao         ###   ########.fr       */
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

void	update(t_command *cmd, t_exec *exec)
{
	if (exec->pipefd[0] > 2)
		dup2(exec->pipefd[0], exec->keeper);
	ft_close(&exec->pipefd[0]);
	ft_close(&exec->pipefd[1]);
	if (entry_found("_"))
		update_var("_", *cmd->cmd);
}
