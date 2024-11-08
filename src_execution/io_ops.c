/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:40:49 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/08 12:33:52 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update(t_command *cmd, t_exec *exec)
{
	if (exec->pipefd[0] > 2)
		dup2(exec->pipefd[0], exec->keeper);
	ft_close(&exec->pipefd[0]);
	ft_close(&exec->pipefd[1]);
	if (entry_found("_"))
		update_var("_", *cmd->cmd);
}
