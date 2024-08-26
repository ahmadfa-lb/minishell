/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/26 06:47:04 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void parse_redirections(t_list_tokens **tokens_list, t_list_tokens **redir_list) {
    t_list_tokens *token = *tokens_list;

    while (token) {
        if (is_redirector(token->type)) {
            t_list_tokens *file_token = token->next;
            if (!file_token) {
                printf("Syntax error: expected a file after redirector.\n");
                break;
            }

            // Create new nodes for the redirector and its associated file
            t_list_tokens *redir_node = create_token_node(token->type, NO_QUOTE, token->value, false);
            t_list_tokens *file_node = create_token_node(file_token->type, file_token->quote_type, file_token->value, file_token->space);
            
            // Append them to the redir_list
            append_token(redir_list, redir_node);
            append_token(redir_list, file_node);

            // Remove the redirector and its associated file from the tokens list
            token = remove_token(tokens_list, token);     // Remove redirector
            token = remove_token(tokens_list, file_token); // Remove associated file
        } else {
            token = token->next;
        }
    }
}



