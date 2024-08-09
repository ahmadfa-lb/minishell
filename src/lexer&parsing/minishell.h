/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:57 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/09 16:43:13 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/inc/libft.h"

/* Standard Input/Output functions */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

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
// # include "art.h"

# define SUCCESS 0
# define FAILURE 1

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ERROR,
    TOKEN_FILENAME
}	t_tokens_type;

typedef struct s_token
{
	t_tokens_type   type;
	char			*value;
	struct	s_token	*next;
}	t_list_tokens;


typedef struct s_cmd
{
    t_list_tokens   tokens_list;
	char			**cmd;
	int				status;
	int				running;
	pid_t			pid;
}					t_cmd;

typedef struct s_data
{
	t_cmd			*cmd;
    char            **env;
	char			*user_input;
}					t_data;

extern int			signal_number;
void				art(void);
char				*get_path(char *cmd, char **env);
void				initcmd(const char *input, char **env, t_data *data);
void				runcmd(const char *input, char **env, t_data *data);
void				noninteractivehandle_sigquit(int sig);
void				noninteractivehandle_sigint(int sig);
void				interactivehandle_sigquit(int sig);
void				interactivehandle_sigint(int sig);
void				handlesignal(t_data *data);



//tokenization_helpers.c
int					ft_isspace(char c);
void				ft_skip_whitespace(char **input);
char 				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strnlen(const char *str, size_t n); 
char				*ft_strndup(const char *s, size_t n);

//cmd_to_tokens.c
char				*find_quoted_string(char **input, char quote);
char				*collect_word(char **input);
char				*concatenate_quoted_substrings(char *input);
t_list_tokens		*create_token(t_tokens_type type, char *value);
void				append_token(t_list_tokens **tokens,
					t_list_tokens *new_token);
t_list_tokens		*add_token(t_list_tokens **tokens,
					t_tokens_type type, char *value);
void				tokenize(char *input, t_list_tokens **tokens);
void				free_tokens(t_list_tokens *tokens);
void				handle_quoted_input(char *string, char *new_string,
					void (*copy_or_count)(char *, int *, char), int *count);
void				count_length(char *new_string, int *count, char c);
void				copy_char(char *new_string, int *count, char c);
bool				remove_quotes_from_string(char **string);
bool				remove_quotes_from_tokens(t_list_tokens *tokens);

#endif




