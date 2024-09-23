/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:45:40 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/20 22:31:04 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES //

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define MALLOC_ERROR -77

# define WORD 0
# define PIPE 1
# define INPUT 2  // cat < Makefile cat Makefile
# define OUTPUT 3 // ls > out ==== ls than 7titiha f out
# define APPEND 4
# define HEREDOC 5 // << delimiter
# define AMBIG 6

typedef struct s_trash
{
	void				*address;
	struct s_trash		*next;
}						t_trash;

typedef struct s_env
{
	char				*name;
	char				*value;
	char				*line;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_tockens
{
	char				*word;
	char				**word_after_exp;
	int					type;
	bool				ambiguous;
	char				*dollar;
	struct s_tockens	*next;
	struct s_tockens	*prev;
}						t_tockens;

typedef struct	s_redir
{
	int					type;
	char				*file_name;
	struct s_redir		*next;
} 						t_redir;

typedef struct	s_command
{
	char 				**cmd;
	t_redir				*red;
	struct s_command	*next;
}						t_command;



typedef struct	s_program
{
	t_trash				*trash_list;
	t_env				*env_list;
	t_tockens			*tocken_list;
	t_command			*command_list;
	bool				double_flag;
	bool				single_flag;
	int					ret_value;
	int					last_ret_value;
	int 				i;
	int					j;
}						t_program;

// FUNCTIONS //



void					get_env(t_env **env_list, char **env);
t_trash					*ft_add_trash(t_trash **head, void *addr);
void					free_trash(t_trash **head);
int						count_words(char *line);
int						word_lenght(char *line);
char					**split_mgem7a(char *line);
void					tockenizing(char *line);
t_tockens				*ft_add_tocken(char *word, int type, bool ambg, char *dollar);
void					ft_white_spaces(char *line);
int						valid_quotes(char *line);
void					ft_free_exit(char *line, bool exit);
int						is_whitespace(int c);
int						line_len(char *line);
char					*add_space(char *line);
int						syntax_error(void);
void    				expand(void);
void				    split_tokens(void);



t_redir	*ft_add_redir(t_redir **head, char *file_name, int type);
t_command	*ft_add_command(t_command **head, char **commands, t_redir *redir);
void    fill_command_list(void);

extern t_program		g_data;
#endif