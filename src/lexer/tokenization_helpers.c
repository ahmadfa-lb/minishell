/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/15 07:38:25 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to append a token to the list
void append_token(t_list_tokens **tokens, t_list_tokens *new_token)
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
	return (result);
}

// Free the token list
void	free_tokens(t_list_tokens *tokens)
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

void ft_token_join(t_list_tokens **tmp, t_list_tokens **to_del)
{
	(*to_del) = (*tmp)->next;
	if (ft_strlen((*tmp)->value) == 1 && !ft_strncmp((*tmp)->value, "$", 1)
		&& (*tmp)->quote_type == NO_QUOTE)
	{
		free((*tmp)->value);
		(*tmp)->value = ft_strdup((*tmp)->next->value);
	}
	else
		(*tmp)->value = ft_strjoin((*tmp)->value, (*tmp)->next->value);
}

void ft_free_node(t_list_tokens **tokens, t_list_tokens *del)
{
	t_list_tokens *tmp;
	
	if (!tokens || !*tokens)
		return ;
	if (*tokens == del)
	{
		*tokens = (*tokens)->next;
		if (del->value)
			free (del->value);
		free(del);
		del = NULL;
		return ;
	}
	tmp = *tokens;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	if (del->value)
		free(del->value);
	free(del);
	del = NULL;
}

void concate_nodes(t_list_tokens **list_token)
{
	t_list_tokens *tmp;
	t_list_tokens *del = NULL;
	
	if (!list_token || !*list_token )
		return ;
	tmp = *list_token;
	while (tmp && tmp->next)
	{
		if (tmp->space == 0)
		{
			ft_token_join(&tmp, &del);//utiles
			if (tmp->next->space == 1)
				tmp = tmp->next->next;
			ft_free_node(list_token, del);//utiles
		}
		else
			tmp = tmp->next;
	}
}


