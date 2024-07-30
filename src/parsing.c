/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:43:55 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 05:40:56 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

t_list_tokens *add_token(t_list_tokens **tokens, t_list_tokens_type type, char *value) {
    t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
    new_token->type = type;
    new_token->value = value;
    new_token->next = NULL;

    if (*tokens == NULL) {
        *tokens = new_token;
    } else {
        t_list_tokens *tmp = *tokens;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
    return (new_token);
}

t_list_tokens *tokenize(char *input) {
    t_list_tokens *tokens = NULL;

    while (*input) {
        while (isspace(*input)) input++;  

        if (*input == '|') {
            add_token(&tokens, TOKEN_PIPE, "|");
            input++;
        } else if (*input == '<' && *(input + 1) == '<') {
            add_token(&tokens, TOKEN_HEREDOC, "<<");
            input += 2;
        } else if (*input == '<') {
            add_token(&tokens, TOKEN_REDIRECT_IN, "<");
            input++;
        } else if (*input == '>' && *(input + 1) == '>') {
            add_token(&tokens, TOKEN_APPEND, ">>");
            input += 2;
        } else if (*input == '>') {
            add_token(&tokens, TOKEN_REDIRECT_OUT, ">");
            input++;
        } else if (*input == '\'' || *input == '"') {
            char quote = *input++;
            char *start = input;
            while (*input && *input != quote) input++;
            if (*input == quote) {
                add_token(&tokens, TOKEN_WORD, strndup(start, input - start));
                input++;
            } else {
                add_token(&tokens, TOKEN_ERROR, "Unclosed quote");
                break;
            }
        } else {
            char *start = input;
            while (*input && !isspace(*input) && *input != '|' && *input != '<' && *input != '>')
                input++;
            add_token(&tokens, TOKEN_WORD, strndup(start, input - start));
        }
    }

    add_token(&tokens, TOKEN_EOF, NULL);  // End of input
    return tokens;
}