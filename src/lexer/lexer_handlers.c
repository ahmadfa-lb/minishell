/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 04:22:44 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pipe_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token;
	char			*pipe;

	pipe = ft_strdup("|");
	new_token = create_token_node(TOKEN_PIPE, NO_QUOTE, pipe, true);
	if (!new_token)
	{
		free(pipe);
		return ;
	}
	free(pipe);
	append_token(tokens, new_token);
	(*current)++;
}

void	handle_redirection_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token;
	char			redirect_char;
	size_t			len;
	char			*token_value;
	int				token_type;

	len = 1;
	redirect_char = **current;
	if (*(*current + 1) == redirect_char)
	{
		len++;
		(*current)++;
	}
	token_value = ft_strndup(*current - len + 1, len);
	if (!token_value)
		return ;
	token_type = determine_token_type(**current, len);
	new_token = create_token_node(token_type, NO_QUOTE, token_value, true);
	if (!new_token)
	{
		free(token_value);
		return ;
	}
	(append_token(tokens, new_token), free(token_value));
	(*current)++;
}

void	handle_quoted_string_token(char **current, t_list_tokens **tokens)
{
	char			quote_type;
	char			*quoted_string;
	t_list_tokens	*new_token;
	bool			space;
	int				token_quote;

	quote_type = **current;
	quoted_string = process_quoted_string(current, quote_type, &space);
	if (!quoted_string)
		return ;
	if (quote_type == '"')
		token_quote = DOUBLE_QUOTE;
	else
		token_quote = SINGLE_QUOTE;
	new_token = create_token_node(TOKEN_WORD, token_quote,
			quoted_string, space);
	if (!new_token)
	{
		free(quoted_string);
		return ;
	}
	append_token(tokens, new_token);
	free(quoted_string);
	(*current)++;
}

void	handle_unquoted_word_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token;
	char			*start;
	char			*value;
	char			*temp;
	bool			space;

	start = *current;
	while (**current && !ft_isspace(**current) && **current != '|'
		&& **current != '<' && **current != '>' && **current != '"'
		&& **current != '\'')
		(*current)++;
	if (*current > start)
	{
		space = !(*(*current) && (*(*current) == '\'' || *(*current) == '"'));
		value = ft_strndup(start, *current - start);
		if (!value)
			return ;
		temp = value;
		new_token = create_token_node(TOKEN_WORD, NO_QUOTE, temp, space);
		if (!new_token)
			return (free(value), (void)0);
		(append_token(tokens, new_token), free(value));
	}
}
