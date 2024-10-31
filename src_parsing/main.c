/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:44:05 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/31 20:38:39 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_program g_data;

void	io_reset()
{
	int fd;

	fd = -1;
	fd = open("/dev/tty", O_RDWR);
	if (fd == -1)
		return(ft_putendl_fd("Error: Failed to open /dev/tty", 2));
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(fd, STDOUT_FILENO) == -1)
		return (ft_putendl_fd("Error: Failed to reset I/O", 2));
	ft_close(fd);
}

void print_tokens()
{
	t_command	*token;
	t_redir		*redirection;
	int			i;

	token = g_data.command_list;
	while (token)
	{
		i = 0;
		redirection = token->red;
		while (token->cmd && token->cmd[i])
		{
			printf(" command %i is '%s'\n", i, token->cmd[i]);
			i++;
		}
		while (redirection)
		{
			printf(" type is %d file name is %s\n", token->red->type, token->red->file_name);
			redirection = redirection->next;
		}
		token = token->next;
		printf("========================================================\n");
	}
}

void init_data(void)
{
	// g_data.env_list = NULL;
	g_data.trash_list = NULL;
	g_data.command_list = NULL;
	g_data.token_list = NULL;
	g_data.double_flag = false;
	g_data.single_flag = false;
	g_data.i = 0;
	g_data.j = 0;
}


static void free_env_list(void)
{
	t_env	*tmp;

	tmp = g_data.env_list;
	while(tmp)
	{
		free(tmp->line);
		free(tmp->name);
		free(tmp->value);
		tmp = tmp->next;
		free(g_data.env_list);
		g_data.env_list = tmp;
	}

}

// static void	print_env()
// {
// 	t_env *tmp;

// 	tmp = g_data.env_list;
// 	while (tmp)
// 	{
// 		printf("name is %s value is %s\n", tmp->name, tmp->value);
// 		tmp = tmp->next;
// 	}
// }

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.ret_value = 130;
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(3);
	}
}

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	line = NULL;
	g_data.ret_value = 0;
	get_env(&g_data.env_list, env);
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
	while (1)
	{
		init_data();
		line = readline("Minihell==>>$ ");
		if (line && *line)
			add_history(line);
		ft_white_spaces(line);
		if (!valid_quotes(line))
		{
			printf("Error: Unclosed quotes detected.\n");
			g_data.ret_value = 2;
			ft_free_exit(line, false);
			continue;
		}
		line = add_space(line);
		tokenizing(line);
		if (syntax_error() == -1)
		{
			g_data.ret_value = 2;
			ft_free_exit(line, false);
			continue;
		}
		expand();
		split_tokens();
		fill_command_list();
		print_tokens();
		executor();
		io_reset();
		ft_free_exit(line, false);
	}
	free_env_list();
}
