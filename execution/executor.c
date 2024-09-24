#include "../inc/minishell.h"

void	executor(void)
{
	char	*cmd;
	e_enum	flag_env;

	cmd = g_data.command_list->cmd[0];
	if (!ft_strncmp(cmd, "cd", 2))
		ft_cd();
	else if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd, "env", 3))
		ft_env(PRINT);
	else if (!ft_strncmp(cmd, "unset", 5))
		ft_unset();
}