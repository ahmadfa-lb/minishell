/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:10:44 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/13 13:13:00 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/inc/libft.h"

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
	struct s_token *next;
} t_list_tokens;

// Helper function to append a token to the list
static void append_token(t_list_tokens **tokens, t_list_tokens *new_token)
{
	t_list_tokens *last = *tokens;
	if (!last)
	{
		*tokens = new_token;
		return;
	}
	while (last->next)
	{
		last = last->next;
	}
	last->next = new_token;
}
// Check is the char is a delimiter
int is_delimiter(char c)
{
	if (c == '"' || c == '\'')
	{
		return (1);
	}
	if (c == '|')
	{
		return (1);
	}
	if (c == '>' || c == '<')
	{
		return (1);
	}
	return (0);
}
// Function to join two strings and free the old ones
static char *strjoin_and_free(char *s1, char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	if (!result)
	{
		free(s1);
		free(s2);
		return NULL;
	}
	strcpy(result, s1);
	strcat(result, s2);
	free(s1);
	free(s2);
	return result;
}

// Function to process quoted strings
static char *process_quoted_string(char **input, char quote_type)
{
	char *start = ++(*input); // Skip the opening quote
	char *end;
	char *result;
	size_t len;

	while (**input && **input != quote_type)
	{
		if (**input == '\\' && (*(*input + 1) == quote_type || *(*input + 1) == '\\'))
		{
			(*input)++; // Skip escaped character
		}
		(*input)++;
	}

	end = *input;
	if (**input == quote_type)
	{
		(*input)++; // Skip closing quote
	}

	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return NULL;
	strncpy(result, start, len);
	result[len] = '\0';

	return result;
}

void handle_pipe(char **current, t_list_tokens **tokens, t_list_tokens **last_token, char **last_valid_position)
{
	t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
		return;

	new_token->type = TOKEN_PIPE;
	new_token->value = strdup("|");
	new_token->quote_type = NO_QUOTE; // No quotes around pipes
	new_token->next = NULL;

	append_token(tokens, new_token);
	*last_token = new_token;
	(*current)++;
	*last_valid_position = *current;
}

void handle_redirection(char **current, t_list_tokens **tokens, t_list_tokens **last_token, char **last_valid_position)
{
	char redirect_char = **current;
	char *redirect_str = (redirect_char == '<') ? "<" : ">";
	size_t len = 1;
	if (*(*current + 1) == redirect_char)
	{
		redirect_str = (redirect_char == '<') ? "<<" : ">>";
		len++;
		(*current)++;
	}

	t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
		return;

	new_token->type = (redirect_char == '<') ? TOKEN_REDIRECT_IN : (len == 2) ? TOKEN_HEREDOC
																			  : TOKEN_REDIRECT_OUT;
	new_token->value = strndup(redirect_str, len);
	new_token->quote_type = NO_QUOTE; // No quotes around redirections
	new_token->next = NULL;

	append_token(tokens, new_token);
	*last_token = new_token;
	(*current)++;
	*last_valid_position = *current;
}

void tokenize(char *input, t_list_tokens **tokens)
{
	char *current = input;
	char *start;
	t_list_tokens *last_token = NULL;
	int in_quote = 0; // Flag to check if we are inside a quote
	char quote_type = NO_QUOTE;
	char *last_valid_position = input; // Track the last valid position

	while (*current)
	{
		// Handle pipes
		if (*current == '|')
		{
			handle_pipe(&current, tokens, &last_token, &last_valid_position);
			continue;
		}

		// Handle redirections
		if (*current == '<' || *current == '>')
		{
			handle_redirection(&current, tokens, &last_token, &last_valid_position);
			continue;
		}

		// Handle quoted strings
		if (*current == '"' || *current == '\'')
		{
			in_quote = 1;
			quote_type = *current;
			if (in_quote)
			{
				// Close existing quote
				if (quote_type == *current)
				{
					char quote = *current;
					char *quoted_string = process_quoted_string(&current, quote);
					if (!quoted_string)
						return;

					t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
					if (!new_token)
					{
						free(quoted_string);
						return;
					}

					new_token->type = TOKEN_WORD;
					new_token->value = quoted_string;
					new_token->quote_type = (quote == '"') ? DOUBLE_QUOTE : SINGLE_QUOTE;
					new_token->next = NULL;

					append_token(tokens, new_token);
					last_token = new_token;
					in_quote = 0;
					last_valid_position = current;
					continue;
				}
			}
		}

		if (in_quote)
		{
			// Create token for remaining input after the last valid position
			if (last_valid_position < current)
			{
				t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
				if (!new_token)
					return;

				new_token->type = TOKEN_WORD;
				new_token->value = strndup(last_valid_position, current - last_valid_position);
				new_token->quote_type = NO_QUOTE; // Unclosed quote implies no specific quote type
				new_token->next = NULL;

				append_token(tokens, new_token);
				last_token = new_token;
			}
		}

		// Handle words (non-quoted strings)
		start = current;
		while (*current && !isspace(*current) && !is_delimiter(*current))
		{
			current++;
		}
		if (current > start)
		{
			t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
			if (!new_token)
				return;

			new_token->type = TOKEN_WORD;
			new_token->value = strndup(start, current - start);
			new_token->quote_type = NO_QUOTE; // No quotes around words
			new_token->next = NULL;

			if (last_token && last_token->type == TOKEN_WORD)
			{
				last_token->value = strjoin_and_free(last_token->value, new_token->value);
				free(new_token);
			}
			else
			{
				append_token(tokens, new_token);
				last_token = new_token;
			}
			last_valid_position = current;
		}

		current++;
	}
}

// Free the token list
void free_tokens(t_list_tokens *tokens)
{
	while (tokens)
	{
		t_list_tokens *next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

// Convert token type to string
const char *token_type_to_string(t_tokens_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return "TOKEN_WORD";
	case TOKEN_PIPE:
		return "TOKEN_PIPE";
	case TOKEN_REDIRECT_IN:
		return "TOKEN_REDIRECT_IN";
	case TOKEN_REDIRECT_OUT:
		return "TOKEN_REDIRECT_OUT";
	case TOKEN_APPEND:
		return "TOKEN_APPEND";
	case TOKEN_HEREDOC:
		return "TOKEN_HEREDOC";
	case TOKEN_ERROR:
		return "TOKEN_ERROR";
	default:
		return "UNKNOWN";
	}
}

const char *quote_type_to_string(t_quote_type quote_type)
{
	switch (quote_type)
	{
	case DOUBLE_QUOTE:
		return "DOUBLE_QUOTE";
	case SINGLE_QUOTE:
		return "SINGLE_QUOTE";
	default:
		return "NO_QUOTE";
	}
}

// Test the lexer
int main(void)
{
	char *input;
	t_list_tokens *tokens = NULL;

	while ((input = readline("minishell> ")) != NULL)
	{
		if (*input == '\0')
		{
			free(input);
			continue;
		}

		add_history(input);

		tokenize(input, &tokens);

		t_list_tokens *current_token = tokens;
		while (current_token)
		{
			printf("Token: %s, Value: %s, quote_type: %s\n",
				   token_type_to_string(current_token->type),
				   current_token->value,
				   quote_type_to_string(current_token->quote_type));
			current_token = current_token->next;
		}

		free_tokens(tokens);
		tokens = NULL;
		free(input);
	}

	printf("\nExiting minishell...\n");
	return 0;
}
