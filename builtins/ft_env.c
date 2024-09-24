#include "../inc/minishell.h"

void	printf_env()
{
	t_env	*iter;

	iter = 0;
	iter = g_data.env_list;
	while (iter)
	{
		printf("%s=%s\n", iter->name, iter->value);
		iter = iter->next;
	}
}
void	ft_env(e_enum flag)
{

	if (flag == PRINT)
		
}
