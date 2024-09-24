#include "../inc/minishell.h"

void	ft_cd(void)
{
	char	*path;

	path = g_data.command_list->cmd[1];
	printf("%s\n", path);
	printf("HERE\n");
	if (chdir(path) == -1)
		ft_putstr_fd(strerror(errno), 2);
}

// int main()
// {
// 	ft_cd;
// 	return (0);
// }