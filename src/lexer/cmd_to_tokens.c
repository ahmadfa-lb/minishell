/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/26 11:12:54 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The lexer is responsible for breaking down the input string into tokens
// that can be further processed by the parser.

#include "../../includes/minishell.h"

// Helper function to handle pipe tokens
static void handle_pipe_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char *pipe;

	pipe = ft_strdup("|");
	new_token = create_token_node(TOKEN_PIPE, NO_QUOTE, pipe, true);
	if (!new_token)
	{
		free(pipe);
		return;
	}

	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle redirection tokens
static void handle_redirection_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char redirect_char;
	size_t len;

	len = 1;
	redirect_char = **current;
	if (*(*current + 1) == redirect_char)
	{
		len++;
		(*current)++;
	}
	new_token = create_token_node(
		(len == 2) ? (redirect_char == '<' ? TOKEN_HEREDOC : TOKEN_APPEND) : (redirect_char == '<' ? TOKEN_REDIRECT_IN : TOKEN_REDIRECT_OUT),
		NO_QUOTE,
		ft_strndup(*current - len + 1, len),
		true);
	if (!new_token)
		return;

	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle quoted string tokens
static void handle_quoted_string_token(char **current, t_list_tokens **tokens)
{
	char quote_type;
	char *quoted_string;
	t_list_tokens *new_token;
	bool space;

	quote_type = **current;
	quoted_string = process_quoted_string(current, quote_type, &space);
	if (!quoted_string)
		return;

	new_token = create_token_node(
		TOKEN_WORD,
		(quote_type == '"') ? DOUBLE_QUOTE : SINGLE_QUOTE,
		quoted_string,
		space);
	if (!new_token)
	{
		free(quoted_string);
		return;
	}
	// free(quoted_string);
	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle unquoted word tokens
// static void	handle_unquoted_word_token(char **current, t_list_tokens **tokens)
// {
// 	t_list_tokens	*new_token;
// 	char			*start;
// 	char			*value;
// 	bool			space;

// 	start = *current;
// 	while (**current && !ft_isspace(**current) && **current != '|' &&
// 		 **current != '<' && **current != '>' && **current != '"' && **current != '\'')
// 	{
// 		(*current)++;
// 	}

// 	if (*current > start)
// 	{
// 		space = !(*(*current) && (*(*current) == '\'' || *(*current) == '"'));
// 		new_token = create_token_node(TOKEN_WORD, NO_QUOTE,value = ft_strndup(start, *current - start), space);
// 		if (!new_token)
// 			return;
// 		if (!new_token)
// 		{
// 			free(value); // Free the memory if the token creation fails.
// 			return;
// 		}
// 		append_token(tokens, new_token);
// 		//free(value);
// 	}
// }

static void handle_unquoted_word_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens *new_token;
	char *start;
	char *value;
	char *val_dup;
	bool space;

	start = *current;
	while (**current && !ft_isspace(**current) && **current != '|' &&
		   **current != '<' && **current != '>' && **current != '"' && **current != '\'')
		(*current)++;
	if (*current > start)
	{
		space = !(*(*current) && (*(*current) == '\'' || *(*current) == '"'));
		value = ft_strndup(start, *current - start);
		if (!value) // Check if memory allocation failed
			return;
		val_dup = ft_strdup(value);
		new_token = create_token_node(TOKEN_WORD, NO_QUOTE, val_dup, space);
		if (!new_token)
			return (free(value), (void)0);
		(append_token(tokens, new_token), free(value));
	}
}

// Tokenize the input string into tokens
void tokenize(char *input, t_list_tokens **tokens)
{
	char *current;

	current = input;
	while (*current)
	{
		while (ft_isspace(*current))
			current++;
		if (*current == '|')
		{
			handle_pipe_token(&current, tokens);
			continue;
		}
		if (*current == '<' || *current == '>')
		{
			handle_redirection_token(&current, tokens);
			continue;
		}
		if (*current == '"' || *current == '\'')
		{
			handle_quoted_string_token(&current, tokens);
			continue;
		}
		handle_unquoted_word_token(&current, tokens);
	}
}
