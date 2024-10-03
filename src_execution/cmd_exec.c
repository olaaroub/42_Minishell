/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 09:59:21 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/30 03:09:58 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		get_fd(t_command *cmd, char *s)
{
	int	fd;
	
	fd = 0;
	if (cmd->red)
	{
		if (!ft_strcmp(s, "in"))
			fd = open(cmd->red->file_name, O_RDONLY);
		else
			fd = -1;
	}
	return (-1);
}

void	child(char *cmd_path, t_command *cmd, int in, int out)
{
	
	if (dup2(in, 0) == -1 || dup2(out, 1) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(in);
	close(out);
	if (execve(cmd_path, g_data.command_list->cmd, NULL) == -1)
		ft_putendl_fd("execve failed", 2);
}

int	execute_cmd(char *cmd_path, t_command *cmd)
{
	/*Will need to enhance the logic in here to avoid redundant code*/
	int	pipefd[2];
	int	pid;
	int	in;
	int	out;
	int keeper;

	if (cmd->red && cmd->red->type == PIPE)
		pipe(pipefd);
	in = get_fd(cmd, "in");
	out = get_fd(cmd, "out");
	pid = fork();
	if (pid == 0)
		child(cmd_path, cmd, in, out);
	else
	{
		close(in);
		close(out);
		if (cmd->red->type == PIPE)
			keeper = pipefd[0];
		
	}
}
