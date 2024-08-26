/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/26 13:40:05 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *create_parser_node(t_list_tokens *command_start)
{
    t_cmd *new_parser = malloc(sizeof(t_cmd));
    if (!new_parser)
        return NULL;
    new_parser->tokens_list = command_start;
    new_parser->list_redirectors = NULL;
    new_parser->next = NULL;
    return new_parser;
}


void split_tokens_by_pipe(t_list_tokens *tokens_list, t_cmd **parser_list) {
    t_list_tokens *current_token = tokens_list;
    t_list_tokens *command_start = tokens_list;

    while (current_token) {
        if (current_token->type == 1) {
            // Create a new parser node for the current command
            t_cmd *new_parser = create_parser_node(command_start);

            // Append the parser node to the parser list
            append_parser_node(parser_list, new_parser);

            // Break the link at the pipe and move to the next command
            t_list_tokens *next_command = current_token->next;
            current_token->next = NULL;
            command_start = next_command;
        }
        current_token = current_token->next;
    }

    // Add the last command as a parser node
    if (command_start) {
        t_cmd *new_parser = create_parser_node(command_start);
        append_parser_node(parser_list, new_parser);
    }
}


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



