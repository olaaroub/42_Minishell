#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char 	*path;

	path = 0;
	path = getcwd(path, 0);
	if (!path)
		return (ft_putstr_fd(strerror(errno), 2));
	printf("%s\n", path);
	free(path);
}
