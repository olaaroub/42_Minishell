/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:44:05 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/27 09:58:22 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_program g_data;

void print_tokens()
{
	t_command *token;
	int i;

	token = g_data.command_list;
	while (token)
	{
		i = 0;
		while (token->cmd && token->cmd[i])
		{
			printf(" command %i is '%s'\n", i, token->cmd[i]);
			i++;
		}
		while (token->red)
		{
			printf(" type is %d file name is %s\n", token->red->type, token->red->file_name);
			token->red = token->red->next;
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
	g_data.tocken_list = NULL;
	g_data.double_flag = false;
	g_data.single_flag = false;
	g_data.i = 0;
	g_data.j = 0;
}

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	line = NULL;
	g_data.ret_value = 0;
	get_env(&g_data.env_list, env);
	while (1)
	{
		init_data();
		line = readline("Minihell==>>$ ");
		if (line && *line)
			add_history(line);
		// if (line && !ft_strcmp(line, "exit"))
		// 	ft_free_exit(line, true);
		ft_white_spaces(line);
		if (!valid_quotes(line))
		{
			printf("Error: Unclosed quotes detected.\n");
			g_data.ret_value = 2;
			ft_free_exit(line, false);
			continue;
		}
		line = add_space(line);
		tockenizing(line);
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
		free (line);
	}
	ft_free_exit(line, false);
}
