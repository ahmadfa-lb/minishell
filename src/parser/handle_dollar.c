/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/21 04:58:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void append_node(t_env **head, char *key, char *value)
// {
//     t_env *new_node;
//     t_env *current;

//     new_node = create_node(key, value);
//     if (!new_node)
//         return;
//     if (*head == NULL)
//         *head = new_node;
//     else
//     {
//         current = *head;
//         while (current->next)
//             current = current->next;
//         current->next = new_node;
//     }
// }







// // for testing

// void print_list(t_env *env_head)
// {
//     t_env *current_env;
//     char *current_value;

//     current_env = env_head;
//     while (current_env)
//     {
//         // Print the key
//         printf("Key: %s\n", current_env->key);
//         // Print the values
//         current_value = current_env->value;
//         printf("Values: ");
//         printf("%s", current_value);
//         printf("\n\n"); // Print a newline between entries
//         // Move to the next env node
//         current_env = current_env->next;
//     }
// }

// int count_envp_elements(char **envp)
// {
// 	int count = 0;
// 	while (envp[count] != NULL)
// 	{
// 		count++;
// 	}
// 	return (count);
// }

// int list_length(t_env *head)
// {
// 	int length = 0;
// 	t_env *current = head;
// 	while (current)
// 	{
// 		length++;
// 		current = current->next;
// 	}
// 	return (length);
// }


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
        if (ft_isspace(str[i + 1]) && str[i] == char_to_remove)
        {
            *ptr++ = str[i++];
            *ptr++ = str[i++]; // Copy the escaped character
        }
        else if (str[i] != char_to_remove)
            *ptr++ = str[i++];
        else if (str[i] == char_to_remove && str[i + 1] == '\0')
            *ptr++ = str[i++];
        else
            i++;
    }
    *ptr = '\0';
    return result;
}

// Function to parse and replace environment variables
char	*handle_dollar_signe(char *input, t_env *envp_head)
{
    int		i;
    int		start;
    int		end;
    char	*sub_env;
    input = handle_double_dollar(input);

    i = 0;
    while (input[i])
    {
        if (input[i] == '$' && ft_isdigit(input[i + 1]))
        {
            sub_env = ft_substr(input, i, 2);
            replace_envp(&input, sub_env, "");
            free(sub_env);
            i += 2;
        }
        else if (input[i] == '$')
        {
            i++;
            start = i;
            while (input[i] && !ft_isspace(input[i]) && !ft_is_delimiter(input[i]) || input[i] == '_')
                i++;
            end = i;
            sub_env = ft_substr(input, start, end - start);
            char *env_value = get_env(envp_head, sub_env);
            if (env_value)
                replace_envp(&input, sub_env, env_value);
            else
                replace_envp(&input, sub_env, "");
            free(sub_env);
        }
        else
            i++;
    }
    return remove_char(input, '$');
}

