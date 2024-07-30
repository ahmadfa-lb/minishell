/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:44:22 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 05:08:33 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
#include <stdlib.h>

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ERROR,
    TOKEN_EOF
} t_list_tokens_type;

typedef struct s_token
{
	t_list_tokens_type	type;
	char			*value;
	struct	s_token	*next;
}	t_list_tokens;

#endif