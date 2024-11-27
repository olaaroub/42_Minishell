/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:45:40 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/27 06:47:17 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES //

# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <wait.h>

# define RED "\033[31m"
# define ITALIC "\033[3m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"

# define WORD 0
# define PIPE 1
# define INPUT 2
# define OUTPUT 3
# define APPEND 4
# define HEREDOC 5
# define AMBIG 6
# define MALLOC_ERROR -69

typedef struct s_trash
{
	void				*address;
	struct s_trash		*next;
}						t_trash;

typedef struct s_vars
{
	int					i;
	int					j;
	int					len;
	char				quote;
}						t_vars;

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
	char				*heredoc;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**cmd;
	int					heredoc;
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
	bool				delim_flag;
	int					ret_value;
	int					i;
	int					j;
}						t_program;

/*						PARSING			*/

/*				get_env.c				*/
void					get_env(t_env **env_list, char **env);
t_env					*env_node(char *env);
t_env					*ft_add_env(t_env **head, char *env);

/*				trash.c					*/
t_trash					*ft_add_trash(t_trash **head, void *addr);
void					free_trash(t_trash **head);
t_trash					*trash_node(void *addr);

/*              export_tools				*/
int						ft_strlen_eq(char *line, char c);
size_t					list_size(void *lst, int s);
int						compare(char *min_str, char *str);
t_env					*get_min(t_env *env);
char					*get_var_name(char *line, int sign);
void					sort_env(t_env **env);
t_env					*env_newnode(char *line);
void					env_add_back(t_env **head, t_env *new_node);
t_env					*env_new_node(char *line, int flag);
t_env					*get_to_print(t_env *env, int index);
void					print_exported_vars(void);

/*						EXPAND			*/
int						expand(void);
void					check_master_quotes(bool *double_flag,
							bool *single_flag,
							char c);
int						check_env_name(char *buff);
int						get_expanded(char *buff, int fd);
void					start_expand(char *buff, int fd);
char					*get_filename(void);

/*						PARSING_FUNCS	*/
char					*trim_quotes(char *word);
int						count_double_quotes(char *line, size_t *i);
int						count_single_quotes(char *line, size_t *i);
void					skip_d_quotes(char *line, int *i);
void					skip_s_quotes(char *line, int *i);
void					free_env_list(void);
int						len_until_pipe(t_tokens *temp);
char					**customized_split(char *line);
void					tokenizing(char *line);
void					ft_white_spaces(char *line);
int						valid_quotes(char *line);
void					ft_free_exit(char *line, bool exit);
int						line_len(char *line);
char					*add_space(char *line);
int						syntax_error(void);
int						split_tokens(void);
int						handle_ambiguous(t_tokens **temp, t_redir **redir,
							char **commands, int *i);

/*				command_list.c			*/
t_redir					*redir_node(char *file_name, int type);
t_command				*command_node(char **commands, t_redir *redir);
t_redir					*ft_add_redir(t_redir **head, char *file_name,
							int type);
t_command				*ft_add_command(t_command **head, char **commands,
							t_redir *redir);
int						fill_command_list(void);
void					sig_handler(int signo);

/*				EXECUTION		*/

typedef struct s_exec
{
	int					pipefd[2];
	char				**paths;
	int					in;
	int					out;
	int					tmp_fd;
	int					save;
	pid_t				pid;
}						t_exec;

/*				EXECUTION_FUNCS	*/

/*				executor.c		*/
int						entry_found(char *to_find);
void					update_var(char *to_find, char *new_value);
t_env					*get_env_node(char *to_find);

/*				fd_operations.c	*/
void					ft_close(int *fd);
void					dup_redirections(t_exec *exec);
void					set_pipes(t_command *cmd, t_exec *exec);
int						set_redirections(t_exec *exec, t_redir *red);
void					update_fd(t_redir *red, t_exec *exec);

/*				getters.c		*/
char					**get_paths(void);
char					*get_cmd_path(t_command *cmd, char **paths);

/*				executors.c		*/
void					execute_builtin(t_exec *exec, t_command *cmd, int flag);
pid_t					execute_cmd(t_command *cmd, t_exec *exec, char **env);

/*				orchestrator.c	*/
void					executor(char **env);
void					prepare_input(t_command *cmd, t_exec *exec, char **env);

/*				identifiers.c	*/
int						is_command(t_command *cmd, char **paths);
int						is_builtin(char *cmd);

/*				heredoc_func.c	*/
int						handle_heredoc(t_redir *red);
int						offset_reposition(int fd, char *name);
char					*create_tmp_file(void);
int						handle_special_chars2(char *word, int *i, int fd);
void					check_delimiter(char *delim);

/*				io_ops.c		*/
void					mod_fds(t_exec *exec);
void					restore_io(int *saved);
int						exit_stat(int stat);

/*				cleaning.c		*/
void					free_arr(char **arr);
void					free_exec(t_exec *exec);
void					free_alloc(void);

int						open_file(t_redir *red, int type);
void					heredoc_counter(t_command *cmd);

/*				utils.c			*/
int						check_fd(t_redir *red, t_exec *exec);
int						get_heredoc(t_redir *red);
void					last_cmd(t_command *cmd, t_exec *exec);
void					saving_pipe(t_command *cmd, t_exec *exec);
int						heredoc_present(t_command *cmd);

/*				BUILTINS		*/
void					ft_cd(t_command *cmd);
void					ft_pwd(void);
void					ft_env(void);
void					ft_unset(t_command *cmd);
void					ft_echo(t_command *cmd);
void					ft_exit(t_command *cmd);
int						ft_export(char **cmd);

extern t_program		g_data;
#endif