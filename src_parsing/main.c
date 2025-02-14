/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:44:05 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/27 06:46:57 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_program	g_data;

static void	init_data(void)
{
	g_data.trash_list = NULL;
	g_data.command_list = NULL;
	g_data.token_list = NULL;
	g_data.double_flag = false;
	g_data.single_flag = false;
	g_data.delim_flag = false;
	g_data.i = 0;
	g_data.j = 0;
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.ret_value = 130;
	}
}

static int	tokenize(char **line)
{
	ft_white_spaces(*line);
	if (!valid_quotes(*line))
	{
		ft_printf(2, "Error: Unclosed quotes detected.\n");
		g_data.ret_value = 2;
		ft_free_exit(*line, false);
		return (-77);
	}
	*line = add_space(*line);
	tokenizing(*line);
	if (syntax_error() == -1)
	{
		g_data.ret_value = 2;
		ft_free_exit(*line, false);
		return (-77);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	line = NULL;
	get_env(&g_data.env_list, env);
	g_data.ret_value = 0;
	while (ac | **av)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		init_data();
		line = readline("minishell$ ");
		signal(SIGINT, SIG_IGN);
		if (!line)
			return (free_env_list(), printf("exit\n"), 0);
		if (line && *line)
			add_history(line);
		if (tokenize(&line) == -77 || fill_command_list() == MALLOC_ERROR)
			continue ;
		free(line);
		executor(env);
		free_trash(&g_data.trash_list);
	}
	free_env_list();
	return (0);
}
