/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/17 02:34:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *my_getenv_from_copy(char *name, t_env *copy_envp)
{
    t_env *current = copy_envp;

    // Traverse the linked list to find the matching key
    while (current)
    {
        if (ft_strcmp(current->key, name) == 0)
        {
            // Found the matching key, concatenate and return the values
            return concatenate_value_list(current->value_head);
        }
        current = current->next;
    }

    // Return NULL if the key is not found
    return (NULL);
}

void replace_envp(char **input, char *old, char *new)
{
    if (!new) // If new is NULL, don't replace
        return;

    char *pos = ft_strnstr(*input, old, ft_strlen(*input));
    if (!pos)
        return;

    int old_len = ft_strlen(old);
    int new_len = ft_strlen(new);
    int input_len = ft_strlen(*input);

    char *new_input = malloc(input_len - old_len + new_len + 1);
    if (!new_input)
        return;

    // Copy part before `old`
    ft_strlcpy(new_input, *input, pos - *input + 1);

    // Append `new`
    ft_strlcat(new_input, new, (pos - *input) + new_len + 1);

    // Append part after `old`
    ft_strlcat(new_input, pos + old_len, input_len - old_len + new_len + 1);

    free(*input);
    *input = new_input;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove all occurrences of a specific character from a string
char *remove_char(char *str, char char_to_remove)
{
    if (!str)
        return NULL;

    int len = strlen(str);
    char *result = malloc(len + 1);
    if (!result)
        return NULL;

    char *ptr = result;
    int i = 0;
    while (i < len)
    {
        if (str[i] == '\\' && str[i + 1] == char_to_remove)
        {
            i++;
            *ptr++ = str[i++]; // Copy the escaped character
        }
        else if (str[i] != char_to_remove)
        {
            *ptr++ = str[i++];
        }
        else
        {
            i++;
        }
    }
    *ptr = '\0';
    return result;
}

// Function to parse and replace environment variables
char *handle_dollar_signe(char *input, t_env *envp_head)
{
    int i = 0;
    int start, end;
    char *sub_env;

    while (input[i])
    {
        if (input[i] == '\\' && input[i + 1] == '$')
        {
            i += 2;
        }
        else if (input[i] == '$')
        {
            i++;
            start = i;
            while (input[i] && !ft_isspace(input[i]) && (ft_isalnum(input[i]) || input[i] == '_'))
                i++;
            end = i;
            sub_env = ft_substr(input, start, end - start);
            char *env_value = my_getenv_from_copy(sub_env, envp_head);
            if (env_value)
                replace_envp(&input, sub_env, env_value);
            free(sub_env);
        }
        else
            i++;
    }
    return remove_char(input, '$');
}

// for test
int main(int argc, char **argv, char **envp)
{
    t_env *copy_envp = NULL;
    char *input;

    // Initialize the copy_envp linked list from envp
    init_copy_envp(&copy_envp, envp);

    while (1)
    {
        input = readline("minishell>>> ");
        if (!input)
        {
            break;
        }
        if (*input)
        {
            add_history(input);
            // Update input after processing using the refactored function
            input = handle_dollar_signe(input, copy_envp);
            printf("%s\n", input);
        }
        free(input);
    }

    // Free the linked list and clean up
    free_list(copy_envp);

    return 0;
}