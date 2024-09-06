/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 09:01:55 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*process_quoted_string(char **input, char quote_type, bool *space)
// {
// 	char	*start;
// 	char	*end;
// 	char	*result;
// 	size_t	len;

// 	start = ++(*input);
// 	*space = true;
// 	while (**input && **input != quote_type)
// 	{
// 		if (**input == '\\' && (*(*input + 1) == quote_type
// 				|| *(*input + 1) == '\\'))
// 			(*input)++;
// 		(*input)++;
// 	}
// 	if (!**input)
// 		return (NULL);
// 	end = *input;
// 	len = end - start;
// 	result = malloc(len + 1);
// 	if (!result)
// 		return (NULL);
// 	(ft_strncpy(result, start, len), result[len] = '\0');
// 	(void)space;
// 	if (*(*input + 1) && !ft_isspace(*(*input + 1)) && *(*input + 1) != '>'
// 		&& *(*input + 1) != '<' && *(*input + 1) != '|')
// 		*space = false;
// 	return (result);
// }

static void	handle_escape_sequence(char **input, char quote_type)
{
	if (**input == '\\' && (*(*input + 1) == quote_type
			|| *(*input + 1) == '\\'))
		(*input)++;
}

char	*process_quoted_string(char **input, char quote_type, bool *space)
{
	char	*start;
	char	*end;
	char	*result;
	size_t	len;

	start = ++(*input);
	*space = true;
	while (**input && **input != quote_type)
	{
		handle_escape_sequence(input, quote_type);
		(*input)++;
	}
	if (!**input)
		return (NULL);
	end = *input;
	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	(ft_strncpy(result, start, len), result[len] = '\0');
	if (*(*input + 1) && !ft_isspace(*(*input + 1)) && *(*input + 1) != '>'
		&& *(*input + 1) != '<' && *(*input + 1) != '|')
		*space = false;
	return (result);
}

t_list_tokens	*create_token_node(t_tokens_type type, t_quote_type quote_type,
	char *value, bool space)
{
	t_list_tokens	*new_token;

	new_token = malloc(sizeof(t_list_tokens));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->quote_type = quote_type;
	new_token->value = ft_strdup(value);
	new_token->space = space;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_list_tokens **tokens, t_list_tokens *new_token)
{
	t_list_tokens	*last;

	last = *tokens;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new_token;
}

int	determine_token_type(char redirect_char, size_t len)
{
	if (len == 2)
	{
		if (redirect_char == '<')
			return (TOKEN_HEREDOC);
		if (redirect_char == '>')
			return (TOKEN_APPEND);
	}
	else
	{
		if (redirect_char == '<')
			return (TOKEN_REDIRECT_IN);
		if (redirect_char == '>')
			return (TOKEN_REDIRECT_OUT);
	}
	return (-1);
}
