/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:54:50 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/27 14:55:01 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **tokens_to_args(t_list_tokens *tokens)
{
    int count;
    t_list_tokens *temp;
    char **args;

    count = 0;
    temp = tokens;
    // Count the number of TOKEN_WORD tokens
    while (temp)
    {
        if (temp->type == TOKEN_WORD)
            count++;
        temp = temp->next;
    }

    // Allocate space for args array (NULL-terminated)
    args = malloc((count + 1) * sizeof(char *));
    if (!args)
        return NULL;

    // Populate the args array with TOKEN_WORD values
    int i = 0;
    while (tokens)
    {
        if (tokens->type == TOKEN_WORD)
            args[i++] = strdup(tokens->value); // Duplicate the token value
        tokens = tokens->next;
    }
    args[i] = NULL; // Null-terminate the array

    return (args);
}

void free_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
