/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 13:09:01 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"

/* Standard Input/Output functions */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <error.h>

/* System and Process Management */
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

/* File system operations */
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
/* Terminal control */
# include <curses.h>
# include <termios.h>

/* Readline library */
# include <readline/history.h>
# include <readline/readline.h>

/* ascii art */
# include "art.h"

# define SUCCESS 0
# define FAILURE 1

extern int	g_signal_number;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				hidden;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ERROR
}	t_tokens_type;

typedef enum e_quote_type
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	NO_QUOTE
}	t_quote_type;

typedef struct s_token
{
	t_tokens_type	type;
	t_quote_type	quote_type;
	char			*value;
	bool			space;
	struct s_token	*next;
}	t_list_tokens;

typedef struct s_cmd
{
	t_list_tokens	*tokens_list;
	t_list_tokens	*list_redirectors;
	char			*command_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmd_list;
	t_env			*env_list;
	t_list_tokens	*first_tokens_list;
	char			**env_array;
	int				nb_pipes;
	int				saved_stdout;
	int				saved_stdin;
	int				pipe_fds[2];
	int				exit_status;	
	char			*user_input;
}	t_data;

void				art(void);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//lexer 
//input_to_tokens_list.c
void				tokenize(char *input, t_list_tokens **tokens);
//lexer_handlers.c
void	handle_pipe_token(char **current, t_list_tokens **tokens);
void	handle_redirection_token(char **current, t_list_tokens **tokens);
void	handle_quoted_string_token(char **current, t_list_tokens **tokens);
void	handle_unquoted_word_token(char **current, t_list_tokens **tokens);
//list_tokens_concatenation.c
void	ft_token_join(t_list_tokens **tmp, t_list_tokens **to_del);
void	ft_free_node(t_list_tokens **tokens, t_list_tokens *del);
void	concate_nodes(t_list_tokens **list_token);
//tokenization_helpers.c
char	*process_quoted_string(char **input, char quote_type, bool *space);
t_list_tokens	*create_token_node(t_tokens_type type, t_quote_type quote_type,
	char *value, bool space);
void	append_token(t_list_tokens **tokens, t_list_tokens *new_token);
int	determine_token_type(char redirect_char, size_t len);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//builtins
int		ft_cd(char **args, t_env *env_list);
int		ft_echo(char **args);
int		ft_env(t_env *env_list);
int		ft_exit(char **args);
int		ft_export(t_env **env_list, char **input);
int		ft_pwd(void);
int		ft_unset(t_env **head, char **keys);
int	check_key(char *key);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//envp
//envp.c
t_env	*create_envp_node(char *key, char *value, int hidden);
void	split_envp(char *envp_str, char **key, char **value);
t_env	*create_envp_list_node(char *envp_str, int hidden);
void	add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node);
t_env	*init_copy_envp_to_list(char **envp);
//env_utils.c
void	setup_initial_environment(t_env **env_list);
void	increment_shell_level(t_env **env_list, int is_hidden);
char	*get_env(t_env *head, const char *key);
int	set_env(t_env **head, const char *key, const char *value, int hidden);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//execute
//execute.c
void	execute_in_child(t_data *data, t_cmd *current_cmd);
int	execute_cmds_in_childs(t_data *data, t_cmd *current_cmd, int num_pipes);
void	exec_one_non_builtin_cmd(t_data *data, t_cmd *current_cmd);
int	execute_cmd_in_parent(t_data *data, t_cmd *current_cmd);			
int					ft_execute_command(t_data *data, t_cmd *current_cmd);
//execution_helpers.c
int	*create_forks(int len);
void	wait_pids_and_get_status(pid_t *pids, int num_pipes, int *last_status);
void	give_status_value(int pid, int *last_status);
int	set_redirection_and_execute(t_data *data, t_cmd *current_cmd);
bool	ft_handle_direct_command(t_data *data, t_cmd *cmd, char *command);
//file_checks_utils.c
bool				ft_is_executable(const char *path);
bool				ft_check_executable(char *input, t_data *data);
bool				ft_check_if_directory(char *input, t_data *data);
bool				ft_check_file_existence(char *input, t_data *data);
bool				ft_check_file_status(char *input, t_data *data);
//builtins_handling.c
int	execute_builtin(char *cmd, char **args, t_data *data);
int	handle_builtin_command(t_cmd *current_cmd, t_data *data);
bool	check_if_builtin(t_cmd *cmd_list);
//path_and_cmd_validation.c
char	*ft_strjoin_path(const char *dir, const char *cmd);
char	*find_executable_in_paths(char **paths, t_cmd *cmd);
bool	is_builtin_command(t_cmd *cmd_list);
bool	ft_lookup_cmd_in_envpaths(t_data *data, t_cmd *cmd);
bool	ft_verify_if_cmd_is_valid(t_data *data, t_cmd *cmd);
//env_list_to_**array_conversion.c
// static int	count_env_variables(t_env *env_list);
// static char	**allocate_env_array(int count);
// static char	*create_env_variable(t_env *env);
char	**env_list_to_array(t_data *data);
//pipe_management.c
int	get_num_pipes(t_cmd *current_cmd);
void	close_parent_pipe(t_cmd *current_cmd, int **pipes, int i);
int	**create_pipes(int num_pipes);
void	close_all_pipes(int **pipes, int num_pipes);
void	set_pipes(t_cmd *current_cmd, int **pipes, int i, int num_pipes);
//cmd_args_and_redirection.c
char	**build_arguments(t_list_tokens *tokens_list);
int	open_and_duplicate(const char *filename, int flags, mode_t mode,
	int target_fd);
int	redirect(t_data *data, t_tokens_type token, t_list_tokens *tokens_list);
void	handle_redirections(t_data *data, t_cmd *current_cmd);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//parser
//cmd_list_manager.c
t_list_tokens	*remove_token(t_list_tokens **tokens_list, t_list_tokens *token);
void	append_cmd_tokens(t_cmd **cmd_list, t_list_tokens *head,
	t_list_tokens *last);
void	append_cmd_node(t_cmd **cmd_list, t_cmd *new_node, t_list_tokens *head,
	t_list_tokens *last);
t_cmd	*create_cmd_node(void);
//cmd_parsing.c
t_list_tokens	*get_last(t_list_tokens *head);
void	split_tokens_by_pipe(t_data *data, t_cmd **cmd_list);
void	append_redirection_tokens(t_cmd *cmd, t_list_tokens *token);
void	process_redirections(t_cmd *cmd, t_list_tokens **token);
void	parse_all_redirections(t_cmd *cmd_list);
//dollar_expanssion.c
void	insert_at(t_list_tokens **tokens, t_list_tokens *current,
	t_list_tokens *new);
t_list_tokens	*dollar_expansion(t_list_tokens *tokens, t_data *data);
//dollar_handling.c
void	handle_normal_variable(char *input, int *i, char **result, t_env *env);
void	handle_two_dollar(char **result, int *i);
void	handle_dollarexitstatus(char **result, int exit_status, int *i);
char	*handle_dollar_sign(char *input, t_env *env, int exit_status);

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//errors_monitoring
//printing_errors.c
void				ft_print_error_message(char *arg1, char *arg2);
void	print_syntax_error(char *error_message, int *exit_status);
//syntax_error.c
char	check_unclosed_quotes(char *input);
bool	check_pipes(t_list_tokens *token_list);
bool	handle_redirection_error(t_list_tokens *next_token, t_data *data);
bool	check_tokens_redirections(t_list_tokens *token_list, t_data *data);
bool	check_initial_errors(char *input, t_data *data);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//heredocs
//heredoc.c
char	*generate_heredoc_filename(char **delimiters, t_data *data,
	t_quote_type quote_type, int i);
char	**get_delimiters(t_list_tokens *redirectors);
char	*handle_heredoc(t_cmd *cmd, t_data *data, int quote_type);
//heredoc_handler_helpers.c
t_list_tokens	*parse_input_to_tokens(char *delimiter);
int	get_delimiters_count(t_list_tokens *redirectors);
void	update_heredoc_data(t_list_tokens **heredoc_tokens, t_data *data,
	t_quote_type quote_type);

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//memory_management
//cleanup_utils.c
void	free_envp_list(t_env *head);
void	free_parser_list(t_cmd *parser_list);
void	free_tokens(t_list_tokens *tokens);
void	free_data(t_data *data);
//cleanup_utils1.c
void	free_args(char **args);
void	free_pipes(int **pipes, int num_pipes);
void	ft_free_split(char **split);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//utils
//ft_string_utils.c
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_strnlen(const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);
//pid_uid_fetcher.c
char	*read_pid_line(int fd);
pid_t	ft_getpid(void);
ssize_t	read_status_file(char *buffer, size_t size);
pid_t	ft_getuid(void);
//utils.c
int	ft_isspace(char c);
void	ft_skip_whitespace(char **input);
int	ft_is_delimiter(char c);
int	is_redirector(int type);
int	ft_cmd_lstsize(t_cmd *lst);
int	get_string_array_length(char **string);
//buitins_utils.c
long long		ft_atoll(const char *str);
void	swap_nodes(t_env *a, t_env *b);
void	sort_env_list(t_env *head);
int		check_key(char *key);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//signals
//signals.c
void	set_signals(void);
void	reset_signals(void);
//signals_helpers.c
void	handle_ctrl_d(t_data *data);
void	handle_ctrl_c(int sig);
void	update_exit_status_on_signal(int *status);
#endif
