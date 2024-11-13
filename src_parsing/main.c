/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:44:05 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/13 00:46:03 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_program g_data;

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
			printf("*cmd->cmd == %p\n", *token->cmd);
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
		// free_exec(g_data.exec); will need to add this to the global struct
		signal(SIGQUIT, SIG_IGN);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

}

int tokenize(char **line)
{
	ft_white_spaces(*line);
	if (!valid_quotes(*line))
	{
		printf("Error: Unclosed quotes detected.\n");
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

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	line = NULL;
	get_env(&g_data.env_list, env);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	g_data.ret_value = 0;
	while (1)
	{
		init_data();
		line = readline("Minihell==>>$ ");
		if(!line)
			return(printf("exit\n"), 0);
		if (line && *line)
			add_history(line);
		if(tokenize(&line) == -77)
			continue;
		fill_command_list();
		// print_tokens();
		executor(env);
		ft_free_exit(line, false);
	}
	free_env_list();
}
