/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 14:21:57 by afarachi         ###   ########.fr       */
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

extern int	signal_number;

typedef struct s_env
{
    char *key;
    char *value;
	int		hidden;
    struct s_env *next;
} t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ERROR
} t_tokens_type;

typedef enum e_quote_type
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	NO_QUOTE
} t_quote_type;

typedef struct s_token
{
	t_tokens_type type;
	t_quote_type quote_type;
	char *value;
	bool  space;
	struct s_token *next;
} t_list_tokens;

typedef struct s_cmd
{
	t_list_tokens	*tokens_list;
    t_list_tokens	*list_redirectors;
	char			*command_path;
	struct s_cmd	*next;
	struct s_cmd    *prev;
}					t_cmd;



typedef struct s_data
{
	t_cmd			*cmd_list;
    t_env           *env_list;
	t_list_tokens	*first_tokens_list;
	char			**env_array;
	int				nb_pipes;
	// pid_t			*pids;
	int				saved_stdout;
    int				saved_stdin;
	int				pipe_fds[2];
	int				exit_status;	
	char			*user_input;
}					t_data;



void				art(void);
// char				*get_path(char *cmd, char **env);
// void				initcmd(const char *input, char **env, t_data *data);
// void				runcmd(const char *input, char **env, t_data *data);
// void				noninteractivehandle_sigquit(int sig);
// void				noninteractivehandle_sigint(int sig);
// void				interactivehandle_sigquit(int sig);
// void				interactivehandle_sigint(int sig);
// void				handlesignal(t_data *data);
bool	check_initial_errors(char *input, t_data *data);
void free_data(t_data *data);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//lexer
//cmd_to_token.c
//static void	handle_pipe_token(char **current, t_list_tokens **tokens);
//static void	handle_redirection_token(char **current, t_list_tokens **tokens);
//static void	handle_quoted_string_token(char **current, t_list_tokens **tokens);
//static void	handle_unquoted_word_token(char **current, t_list_tokens **tokens);
void	tokenize(char *input, t_list_tokens **tokens);
//tokenization_helpers.c
void append_token(t_list_tokens **tokens, t_list_tokens *new_token);
char	*process_quoted_string(char **input, char quote_type, bool *space);
void	free_tokens(t_list_tokens *tokens);
const char *token_type_to_string(t_tokens_type type);
const char *quote_type_to_string(t_quote_type quote_type);
t_list_tokens *create_token_node(t_tokens_type type, t_quote_type quote_type, char *value, bool space);
//tokenization_utils.c
int	ft_isspace(char c);
void	ft_skip_whitespace(char **input);
char	*ft_strncpy(char *dest, const char *src, size_t n) ;
// char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
//tokenization_utils1.c
size_t	ft_strnlen(const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);
int ft_is_delimiter(char c);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//parser
//list_tokens_concatenation.c
void ft_token_join(t_list_tokens **tmp, t_list_tokens **to_del);
void ft_free_node(t_list_tokens **tokens, t_list_tokens *del);
void concate_nodes(t_list_tokens **list_token);
//handle_dollar.c
void	handle_normal_variable(char *input, int *i, char **result, t_env *env);
void	handle_two_dollar(char **result, int *i);
char	*handle_dollar_sign(char *input, t_env *env, int exit_status);
t_list_tokens	*dollar_expansion(t_data *data);
//handle_dollar_utils.c
char	*read_pid_line(int fd);
pid_t	ft_getpid();
ssize_t read_status_file(char *buffer, size_t size);
pid_t ft_getuid();
//handle_redirectors.c
void free_parser_list(t_cmd *parser_list);
t_list_tokens *get_last(t_list_tokens *head);
void split_tokens_by_pipe(t_data *data, t_cmd **cmd_list);
void	parse_all_redirections(t_cmd *cmd_list);
//handle_redirectors_helpers.c
int is_redirector(int type);
t_list_tokens	*remove_token(t_list_tokens **tokens_list, t_list_tokens *token);
void append_cmd_node(t_cmd **cmd_list, t_cmd *new_node, t_list_tokens *head, t_list_tokens *last);
void append_cmd_tokens(t_cmd **cmd_list, t_list_tokens *head, t_list_tokens *last);
t_cmd *create_cmd_node();
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//envp
//env.c
t_env	*create_envp_node(char *key, char *value, int hidden);
void	split_envp(char *envp_str, char **key, char **value);
t_env	*create_envp_list_node(char *envp_str, int hidden);
void	add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node);
t_env	*init_copy_envp_to_list(char **envp);
//env_utils.c
void	free_envp_list(t_env *head);
char	*get_env(t_env *head, const char *key);
int		set_env(t_env **head, const char *key, const char *value, int hidden);
int		unset_env(t_env **head, const char *key);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//execute
//cmd_args_and_redirection.c
char	**build_arguments(t_list_tokens *tokens_list);
int	open_and_duplicate(const char *filename, int flags, mode_t mode, int target_fd);
int	redirect(t_data *data,t_tokens_type token, t_list_tokens *tokens_list);
//env_list_to_**array_conversion.c
// static int	count_env_variables(t_env *env_list);
// static char	**allocate_env_array(int count);
// static char	*create_env_variable(t_env *env);
char	**env_list_to_array(t_data *data);
//execute.c
void	handle_parent_process(t_data *data, int *in_fd);
void	wait_for_children(pid_t *pids, int count, t_data *data);
int		handle_child_process(t_data *data, t_cmd *current_cmd, int in_fd);

int	ft_execute_command(t_data *data, t_cmd *current_cmd);
//execution_process_utils.c
void	handle_redirections(t_data *data, t_cmd *current_cmd);
void	handle_piping(int *pipe_fds, int nb_pipes);
pid_t	handle_forking(void);
int	execute_command(t_cmd *current_cmd, t_data *data);
void	cleanup_fds(t_data *data);
//file_checks_utils.c
bool	ft_is_executable(const char *path);
bool	ft_check_executable(char *input, t_data *data);
bool	ft_check_if_directory(char *input, t_data *data);
bool	ft_check_file_existence(char *input, t_data *data);
bool	ft_check_file_status(char *input, t_data *data);
//path_and_cmd_validation.c
char	*ft_strjoin_path(const char *dir, const char *cmd);
void	ft_free_split(char **split);
char	*find_executable_in_paths(char **paths, t_cmd *cmd);
bool	ft_lookup_cmd_in_envpaths(t_data *data, t_cmd *cmd);
bool	ft_verify_if_cmd_is_valid(t_data *data, t_cmd *cmd);
//adadas
int handle_builtin_command(t_cmd *current_cmd, t_data *data);
bool	check_if_builtin(t_cmd *cmd_list);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//errors_monitoring
//printing_errors.c
void	ft_print_error_message(char *arg1, char *arg2);

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//heredocs
//heredoc.c
char	*generate_heredoc_filename(void);
void	write_heredoc_to_file(const char *filename, const char *content);
char	*read_heredoc_input(const char *delimiter);
char	*handle_heredoc(t_cmd *cmd, t_data *data);


//list to char**
char	**tokens_to_args(t_list_tokens *tokens);

//built-in
int ft_echo(char **args);
int ft_pwd();
int ft_cd(char **args, t_env *env_list);
int	ft_env(t_env *env_list);
int ft_export(t_env **env_list, char **input);
int check_key(char *key) ;
int ft_unset(t_env **head, char **keys);
void free_args(char **args);
void split_envp(char *envp_str, char **key, char **value);
int ft_exit(char **args);

#endif