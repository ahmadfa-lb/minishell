/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 05:53:38 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 08:36:26 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	check_unclosed_quotes(char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (*input == '\"' && single_quote % 2 == 0)
			double_quote++;
		input++;
	}
	if (single_quote % 2 != 0)
		return ('\'');
	if (double_quote % 2 != 0)
		return ('\"');
	return ('\0');
}

bool	check_pipes(t_list_tokens *token_list)
{
	if (token_list && token_list->type == TOKEN_PIPE)
		return (false);
	while (token_list)
	{
		if (token_list->type == TOKEN_PIPE)
		{
			if (!token_list->next || token_list->next->type == TOKEN_PIPE)
				return (false);
		}
		token_list = token_list->next;
	}
	return (true);
}

// bool	check_tokens_redirections(t_list_tokens *token_list, t_data *data)
// {
// 	while (token_list)
// 	{
// 		if (token_list->type == TOKEN_REDIRECT_IN || token_list->type
// 			== TOKEN_APPEND || token_list->type == TOKEN_REDIRECT_OUT
// 			|| token_list->type == TOKEN_HEREDOC)
// 		{
// 			if (!token_list->next || token_list->next->type == TOKEN_PIPE
// 				|| (token_list->next->type >= TOKEN_REDIRECT_IN
// 					&& token_list->next->type <= TOKEN_HEREDOC))
// 			{
// 				if (!token_list->next)
// 					print_syntax_error("newline", &(data->exit_status));
// 				else if (token_list->next->type == TOKEN_PIPE)
// 					print_syntax_error("|", &(data->exit_status));
// 				else if (token_list->next->type == TOKEN_REDIRECT_IN)
// 					print_syntax_error("<", &(data->exit_status));
// 				else if (token_list->next->type == TOKEN_REDIRECT_OUT)
// 					print_syntax_error(">", &(data->exit_status));
// 				else if (token_list->next->type == TOKEN_APPEND)
// 					print_syntax_error(">>", &(data->exit_status));
// 				else if (token_list->next->type == TOKEN_HEREDOC)
// 					print_syntax_error("<<", &(data->exit_status));
// 				return (false);
// 			}
// 		}
// 		token_list = token_list->next;
// 	}
// 	return (true);
// }

bool	handle_redirection_error(t_list_tokens *next_token, t_data *data)
{
	if (!next_token)
		print_syntax_error("newline", &(data->exit_status));
	else if (next_token->type == TOKEN_PIPE)
		print_syntax_error("|", &(data->exit_status));
	else if (next_token->type == TOKEN_REDIRECT_IN)
		print_syntax_error("<", &(data->exit_status));
	else if (next_token->type == TOKEN_REDIRECT_OUT)
		print_syntax_error(">", &(data->exit_status));
	else if (next_token->type == TOKEN_APPEND)
		print_syntax_error(">>", &(data->exit_status));
	else if (next_token->type == TOKEN_HEREDOC)
		print_syntax_error("<<", &(data->exit_status));
	else
		return (false);
	return (true);
}

bool	check_tokens_redirections(t_list_tokens *token_list, t_data *data)
{
	while (token_list)
	{
		if (is_redirector(token_list->type))
		{
			if (!token_list->next || token_list->next->type == TOKEN_PIPE
				|| is_redirector(token_list->next->type))
			{
				if (handle_redirection_error(token_list->next, data))
					return (false);
			}
		}
		token_list = token_list->next;
	}
	return (true);
}

bool	check_initial_errors(char *input, t_data *data)
{
	char	c;

	if (check_unclosed_quotes(input))
	{
		c = check_unclosed_quotes(input);
		if (c == '\'')
			print_syntax_error("'", &(data->exit_status));
		else
			print_syntax_error("\"", &(data->exit_status));
		return (false);
	}
	else if (!check_pipes(data->first_tokens_list))
		return (print_syntax_error("|", &(data->exit_status)), false);
	else if (!check_tokens_redirections(data->first_tokens_list, data))
		return (false);
	return (true);
}
