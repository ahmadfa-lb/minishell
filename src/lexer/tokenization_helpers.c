/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/02 15:09:09 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Helper function to append a token to the list
void append_token(t_list_tokens **tokens, t_list_tokens *new_token)
{
	t_list_tokens *last = *tokens;
	if (!*tokens)
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

// Function to process quoted strings
char	*process_quoted_string(char **input, char quote_type, bool *space)
{
	char *start; // Skip the opening quote
	char *end;
	char *result;
	size_t len;

	start = ++(*input);
	*space = true;
	// non gere
	while (**input && **input != quote_type)
	{
		if (**input == '\\' && (*(*input + 1) == quote_type || *(*input + 1) == '\\'))
			(*input)++;
		(*input)++;
	}
	end = *input;
	
	// if (**input == quote_type)
	// {
	// 	(*input)++; // Skip closing quote
	// }
	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return NULL;
	ft_strncpy(result, start, len);
	result[len] = '\0';

	(void)space;
	 if (*(*input + 1) && !ft_isspace(*(*input + 1)) && *(*input + 1) != '>' && *(*input + 1) != '<' && *(*input + 1) != '|')
	 	*space = false;
	// start = result;
	// free(result);
	return (result);
}

// Free the token list
void	free_tokens(t_list_tokens *tokens)
{
    t_list_tokens *next;

    while (tokens)
    {
        next = tokens->next;
        if (tokens->value)
            free(tokens->value); // Free the value string
        free(tokens); // Free the token structure
		tokens= next;
    }
}


t_list_tokens	*create_token_node(t_tokens_type type, t_quote_type quote_type, char *value, bool space)
{
	t_list_tokens	*new_token;

	new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
	    return NULL;
	new_token->type = type;
	new_token->quote_type = quote_type;
	new_token->value = ft_strdup(value);
	new_token->space = space;
	new_token->next = NULL;
	return (new_token);
}

// t_list_tokens *create_token_node(t_tokens_type type, t_quote_type quote_type, char *value, bool space)
// {
//     t_list_tokens *new_token;

//     new_token = malloc(sizeof(t_list_tokens));
//     if (!new_token)
//         return NULL;
//     new_token->type = type;
//     new_token->quote_type = quote_type;
//     if (value)
//         new_token->value = ft_strdup(value);
//     else
//         new_token->value = NULL;
//     new_token->space = space;
//     new_token->next = NULL;
//     return new_token;
// }


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




