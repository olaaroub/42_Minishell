#include "../inc/minishell.h"

void	ft_cd(void)
{
	char	*path;

	if (!g_data.command_list->cmd[1])
		return ;
	path = g_data.command_list->cmd[1];
	if (chdir(path) == -1)
		ft_putstr_fd(strerror(errno), 2);
}
