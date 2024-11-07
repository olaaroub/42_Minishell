/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:40:49 by hatalhao          #+#    #+#             */
/*   Updated: 2024/11/02 06:05:49 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"

// int	*io_closet()
// {
// 	int	*STDS;

// 	STDS = malloc (sizeof(int) * 2);
// 	STDS[0] = dup(STDIN_FILENO);
// 	STDS[1] = dup(STDOUT_FILENO);
// 	if (STDS[0] == -1 || STDS[1] == -1)
// 		return (free(STDS), NULL);
// 	return (STDS);
// }

// void	io_reset(t_exec *exec, int *STDS)
// {
// 	if (dup2(STDS[0], exec->in) == -1 || dup2(STDS[1], exec->out) == -1)
// 		return (ft_putendl_fd("Error: Failed to reset I/O", 2));
// 	ft_close(&STDS[0]);
// 	ft_close(&STDS[1]);
// }
