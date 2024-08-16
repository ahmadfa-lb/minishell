/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/16 12:52:12 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The lexer is responsible for breaking down the input string into tokens
// that can be further processed by the parser.

#include "../includes/minishell.h"

// Helper function to handle pipe tokens
static void	handle_pipe_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token;

	new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
		return;
	new_token->type = TOKEN_PIPE;
	new_token->value = ft_strdup("|");
	new_token->quote_type = NO_QUOTE;
	new_token->next = NULL;
	new_token->space = 1;
	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle redirection tokens
static void	handle_redirection_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token;
    char			redirect_char;
	size_t			len;
	
	len = 1;
	redirect_char = **current;
	if (*(*current + 1) == redirect_char)
	{
		len++;
		(*current)++;
	}
	new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
		return;
	new_token->type = (redirect_char == '<') ? TOKEN_REDIRECT_IN : TOKEN_REDIRECT_OUT;
	if (len == 2)
		new_token->type = (redirect_char == '<') ? TOKEN_HEREDOC : TOKEN_APPEND;
	new_token->value = ft_strndup(*current - len + 1, len);
	new_token->quote_type = NO_QUOTE;
	new_token->next = NULL;
	new_token->space = 1;
	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle quoted string tokens
static void	handle_quoted_string_token(char **current, t_list_tokens **tokens)
{
	char			quote_type;
	char			*quoted_string;
	t_list_tokens	*new_token;
	bool space = 1;

	quote_type = **current;
	quoted_string = process_quoted_string(current, quote_type, &space);
	if (!quoted_string)
        return;
	new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
	{
		free(quoted_string);
		return;
	}
	new_token->type = TOKEN_WORD;
	new_token->value = quoted_string;
	new_token->quote_type = (quote_type == '"') ? DOUBLE_QUOTE : SINGLE_QUOTE;
	new_token->next = NULL;
	new_token->space = space;
	append_token(tokens, new_token);
	(*current)++;
}

// Helper function to handle unquoted word tokens
static void	handle_unquoted_word_token(char **current, t_list_tokens **tokens)
{
	t_list_tokens	*new_token; 
	char	*start;
	
	start = *current;
	while (**current && !ft_isspace(**current) && **current != '|' &&
		 **current != '<' && **current != '>' && **current != '"' && **current != '\'')
		(*current)++;

	if (*current > start)
	{
		new_token = malloc(sizeof(t_list_tokens));
		if (!new_token)
			return;

		new_token->type = TOKEN_WORD;
		new_token->value = ft_strndup(start, *current - start);
		new_token->quote_type = NO_QUOTE;
		new_token->next = NULL;
		
		new_token->space = 1;
		if (*(*current) && (*(*current) == '\'' || *(*current) == '"'))
			new_token->space = 0;
		append_token(tokens, new_token);
	}
}

// Tokenize the input string into tokens
void	tokenize(char *input, t_list_tokens **tokens)
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
