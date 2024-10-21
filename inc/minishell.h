/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:45:40 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/19 20:26:24 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES //

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <wait.h>
# include <errno.h>
# include <stdbool.h>

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
	int					index;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_tokens
{
	char				*word;
	char				**word_after_exp;
	int					type;
	bool				ambiguous;
	char				*dollar;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}						t_tokens;

typedef struct s_redir
{
	int					type;
	char				*file_name;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*red;
	struct s_command	*next;
}						t_command;

typedef struct s_program
{
	t_trash				*trash_list;
	t_env				*env_list;
	t_tokens			*token_list;
	t_command			*command_list;
	bool				double_flag;
	bool				single_flag;
	int					ret_value;
	int					last_ret_value;
	int					i;
	int					j;
}						t_program;

// FUNCTIONS //
/*						PARSING			*/
/*						PARSING_FUNCS	*/

/*				get_env.c				*/
void					get_env(t_env **env_list, char **env);
t_env					*env_node(char *env);
t_env					*ft_add_env(t_env **head, char *env);

/*				trash.c					*/
t_trash					*ft_add_trash(t_trash **head, void *addr);
void					free_trash(t_trash **head);
t_trash					*trash_node(void *addr);

int						count_words(char *line);
int						word_lenght(char *line);
char					**split_mgem7a(char *line);
void					tokenizing(char *line);
t_tokens				*ft_add_token(char *word, int type, bool ambg, char *dollar);
void					ft_white_spaces(char *line);
int						valid_quotes(char *line);
void					ft_free_exit(char *line, bool exit);
int						is_whitespace(int c);
int						line_len(char *line);
char					*add_space(char *line);
int						syntax_error(void);
void					expand(void);
void					split_tokens(void);

/*				command_list.c			*/
t_redir					*redir_node(char *file_name, int type);
t_command				*command_node(char **commands, t_redir *redir);
t_redir					*ft_add_redir(t_redir **head, char *file_name, int type);
t_command				*ft_add_command(t_command **head, char **commands, t_redir *redir);

void					fill_command_list(void);

/*				EXECUTION		*/
typedef struct s_exec
{
	int					pipefd[2];
	char				**paths;
	int					in;
	int					out;
	int					tmp_fd;
	int					keeper;
	int 				*pid;
}						t_exec;

/*				EXECUTION_FUNCS	*/
/*				executor.c		*/

int						entry_found(char *to_find);
char					*get_pwd(void);
void					update_var(char *to_find, char *new_value);
t_env					*get_env_node(char *to_find);

/*				fd_operations.c	*/
void					ft_close(int fd);
void					dup_redirections(t_exec *exec);
void					set_pipes(t_command *cmd, t_exec *exec);
void					set_redirections(t_exec *exec, t_command *cmd);
void					update_fd(t_command *cmd, t_exec *exec);

/*				getters.c		*/
char					**get_paths(void);
char					*get_cmd_path(t_command *cmd, char	**paths);

/*				executors.c		*/
void					execute_builtin(t_exec *exec, t_command *cmd);
int						execute_cmd(char *cmd_path, t_command *cmd, t_exec *exec);

/*				orchestrator.c	*/
void					executor(void);
void					prepare_input(t_command *cmd, t_exec *exec);
void					command_chain(t_command *cmd, t_exec *exec);

/*				identifiers.c	*/
int	is_command(t_command *cmd, char **paths);
int	is_builtin(char *cmd);

/*				DEBUGGER		*/
void	assist();


/*				BUILTINS		*/
void					ft_cd(void);
void					ft_pwd(void);
void					ft_env(void);
void					ft_unset(void);
void					ft_echo(void);
void					ft_exit(void);

int 					ft_export(char **cmd);


extern t_program		g_data;
#endif