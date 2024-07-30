/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:43:55 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 05:09:10 by afarachi         ###   ########.fr       */
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

t_list_tokens *tokenize(char *input)
{
	t_list_tokens *list_tokens;
	
}