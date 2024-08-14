/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/14 13:12:39 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *my_getenv(char *name, char **env)
{
    int i;
    int j;
    char *sub;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        sub = ft_substr(env[i], 0, j);
        if (ft_strcmp(sub, name) == 0)
        {
            free(sub);
            return (env[i] + j + 1);
        }
        free(sub);
        i++;
    }
    return (NULL);
}

void replace_envp(char **input, char *old, char *new)
{
    char *pos = ft_strnstr(*input, old, ft_strlen(*input));
    if (!pos || !new)
        return;

    int old_len = ft_strlen(old);
    int new_len = ft_strlen(new);
    int diff = new_len - old_len;
    int input_len = ft_strlen(*input);

    char *new_input = malloc(input_len + diff + 1);
    if (!new_input)
        return;

    ft_strlcpy(new_input, *input, pos - *input + 1);            // Copy part before `old`
    ft_strlcat(new_input, new, input_len + diff + 1);           // Append `new`
    ft_strlcat(new_input, pos + old_len, input_len + diff + 1); // Append part after `old`

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
        if (str[i] != '\\' && str[i + 1] != char_to_remove)
        {
            *ptr++ = str[i++];
            *ptr++ = str[i++];
        }
        else if (str[i] != char_to_remove)
            *ptr++ = str[i];
        i++;
    }
    *ptr = '\0';
    return result;
}

// Function to parse and replace environment variables
char *handle_dollar_signe(char *input, char **envp)
{
    int i = 0;
    int start, end;
    char *sub_env;

    while (input[i])
    {
        if (input[i] == '\\' && input[i + 1] == '$')
        {
            i++;
        }
        else if (input[i] == '$')
        {
            i++;
            start = i;
            while (input[i] && !ft_isspace(input[i]) && (ft_isalnum(input[i]) || input[i] == '_'))
                i++;
            end = i;
            sub_env = ft_substr(input, start, end - start);
            replace_envp(&input, sub_env, my_getenv(sub_env, envp));
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
    char *input;

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
            input = handle_dollar_signe(input, envp); // Update input after processing
            printf("%s\n", input);
        }
        free(input);
    }

    return 0;
}
