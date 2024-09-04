/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 05:53:38 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 03:52:13 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_syntax_error(char *error_message, int *exit_status)
{
    // Print syntax error message
    write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(2, error_message, ft_strlen(error_message));
	write(2, "'\n", 2);
    
    // Set exit status to indicate a syntax error
    *exit_status = 2;
}


char check_unclosed_quotes(char *input)
{
    int single_quote = 0;
    int double_quote = 0;

    while (*input)
    {
        if (*input == '\'' && double_quote % 2 == 0)
            single_quote++;
        else if (*input == '\"' && single_quote % 2 == 0)
            double_quote++;
        input++;
    }

    if (single_quote % 2 != 0)
        return '\'';
    if (double_quote % 2 != 0)
        return '\"';
    return '\0';
}

bool check_pipes(t_list_tokens *token_list)
{
    // Check for a leading pipe
    if (token_list && token_list->type == TOKEN_PIPE)
        return false;

    while (token_list)
    {
        if (token_list->type == TOKEN_PIPE)
        {
            if (!token_list->next || token_list->next->type == TOKEN_PIPE)
                return false;
        }
        token_list = token_list->next;
    }

    return true;
}

// bool check_tokens_redirections(t_list_tokens *token_list)
// {
//     while (token_list)
//     {
//         if (token_list->type == TOKEN_REDIRECT_IN || token_list->type == TOKEN_REDIRECT_OUT ||
//             token_list->type == TOKEN_APPEND || token_list->type == TOKEN_HEREDOC)
//         {
//             // Check if a redirection token is followed by another redirection token or pipe
//             if (!token_list->next || token_list->next->type == TOKEN_PIPE ||
//                 (token_list->next->type >= TOKEN_REDIRECT_IN && token_list->next->type <= TOKEN_HEREDOC))
//                 return false;
//         }
//         token_list = token_list->next;
//     }
//     return true;
// }

bool check_tokens_redirections(t_list_tokens *token_list, t_data *data)
{
    while (token_list)
	{	
        if (token_list->type == TOKEN_REDIRECT_IN || token_list->type == TOKEN_REDIRECT_OUT ||
            token_list->type == TOKEN_APPEND || token_list->type == TOKEN_HEREDOC)
        {
            // Check if a redirection token is at the end or followed by another redirection or a pipe
            if (!token_list->next || token_list->next->type == TOKEN_PIPE ||
                (token_list->next->type >= TOKEN_REDIRECT_IN && token_list->next->type <= TOKEN_HEREDOC))
            {
                // Print the error with "newline" if it's the last token
                if (!token_list->next || (!token_list->next->next && token_list->next->type == TOKEN_REDIRECT_OUT))
                    print_syntax_error("newline", &(data->exit_status));
                else if (token_list->next->type == TOKEN_PIPE)
                    print_syntax_error("|", &(data->exit_status));
                else if (token_list->next->type == TOKEN_REDIRECT_IN)
                    print_syntax_error("<", &(data->exit_status));
                else if (token_list->next->type == TOKEN_REDIRECT_OUT)
                    print_syntax_error(">", &(data->exit_status));
                else if (token_list->next->type == TOKEN_APPEND)
                    print_syntax_error(">>", &(data->exit_status));
                else if (token_list->next->type == TOKEN_HEREDOC)
                    print_syntax_error("<<", &(data->exit_status));

                return false;
            }
        }
        token_list = token_list->next;
    }
    return true;
}


bool	check_initial_errors(char *input, t_data *data)
{
	char c;

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
	{
		print_syntax_error("|", &(data->exit_status));
		return (false);
	}
	else if (!check_tokens_redirections(data->first_tokens_list, data))
	{
		// print_syntax_error("<, >, >> or <<", &(data->exit_status));
		// data->exit_status = 2;
		return (false);
	}
	return (true);
}