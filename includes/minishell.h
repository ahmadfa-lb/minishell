/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:57 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/16 13:05:20 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"

/* Standard Input/Output functions */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
    t_list_tokens   *tokens_list;
	int				running;
	pid_t			pid;
}					t_cmd;

typedef struct s_data
{
	t_cmd			*cmd;
    char            **env;
	int				status;	
	char			*user_input;
}					t_data;

// extern int			signal_number;
// void				art(void);
// char				*get_path(char *cmd, char **env);
// void				initcmd(const char *input, char **env, t_data *data);
// void				runcmd(const char *input, char **env, t_data *data);
// void				noninteractivehandle_sigquit(int sig);
// void				noninteractivehandle_sigint(int sig);
// void				interactivehandle_sigquit(int sig);
// void				interactivehandle_sigint(int sig);
// void				handlesignal(t_data *data);



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
//tokenization_utils.c
int	ft_isspace(char c);
void	ft_skip_whitespace(char **input);
char	*ft_strncpy(char *dest, const char *src, size_t n) ;
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
//tokenization_utils1.c
size_t	ft_strnlen(const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);



//parser
//list_tokens_concatenation.c
void ft_token_join(t_list_tokens **tmp, t_list_tokens **to_del);
void ft_free_node(t_list_tokens **tokens, t_list_tokens *del);
void concate_nodes(t_list_tokens **list_token);

#endif




