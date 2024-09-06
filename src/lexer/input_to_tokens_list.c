/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 08:55:42 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize(char *input, t_list_tokens **tokens)
{
	char	*current;

	current = input;
	while (*current)
	{
		while (ft_isspace(*current))
			current++;
		if (*current == '|')
		{
			handle_pipe_token(&current, tokens);
			continue ;
		}
		if (*current == '<' || *current == '>')
		{
			handle_redirection_token(&current, tokens);
			continue ;
		}
		if (*current == '"' || *current == '\'')
		{
			handle_quoted_string_token(&current, tokens);
			continue ;
		}
		handle_unquoted_word_token(&current, tokens);
	}
}
