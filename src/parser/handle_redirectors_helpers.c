/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirectors_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:17:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/26 06:32:49 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_redirector(int type) {
    return (type == '<' || type == '<<' || type == '>' || type == '>>');
}

t_list_tokens *remove_token(t_list_tokens **tokens_list, t_list_tokens *token)
{
    t_list_tokens *current = *tokens_list;

    if (current == token) {
        *tokens_list = token->next;
        free(token->value);
        free(token);
        return *tokens_list;
    }

    while (current && current->next != token)
        current = current->next;

    if (current && current->next == token) {
        current->next = token->next;
        free(token->value);
        free(token);
    }

    return current ? current->next : NULL;
}
