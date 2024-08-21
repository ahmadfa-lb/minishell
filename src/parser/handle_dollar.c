/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/20 10:40:35 by afarachi         ###   ########.fr       */
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

// void free_tab(char **tab)
// {
//     int i;

//     i = 0;
//     while (tab[i])
//     {
//         free(tab[i]);
//         i++;
//     }
//     free(tab);
// }


// free functions
void free_envp_list(t_env *env_head)
{
    t_env *current_env;
    t_env *next_env;

    current_env = env_head;
    while (current_env)
    {
        next_env = current_env->next;
        // Free the key
        free(current_env->key);
        // Free the value list associated with this env node
        free(current_env->value);
        // Free the env node itself
        free(current_env);
        current_env = next_env;
    }
}


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

char *my_getenv_from_copy(char *name, t_env *copy_envp)
{
    t_env *current = copy_envp;

    // Traverse the linked list to find the matching key
    while (current)
    {
        if (ft_strcmp(current->key, name) == 0)
        {
            // Found the matching key, concatenate and return the values
            return current->value;
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



char *handle_double_dollar(char *input)
{
    char *pos;
    char pid_str[12];
    pid_t pid;

    // Get the current process ID
    pid = ft_getpid();
    sprintf(pid_str, "%d", pid);

    // Replace occurrences of $$ with the PID
    while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
    {
        replace_envp(&input, "$$", pid_str);
    }

    return input;
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
        {
            *ptr++ = str[i++];
        }
        else if (str[i] == char_to_remove && str[i + 1] == '\0')
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
    input = handle_double_dollar(input);

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
            char *env_value = my_getenv_from_copy(sub_env, envp_head);
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

// // for test
// int main(int argc, char **argv, char **envp)
// {
//     t_env *copy_envp = NULL;
//     char *input;
//     if (argc > 1)
//     {
//         printf("a%s", argv[1]);
//     }

//     // Initialize the copy_envp linked list from envp
//     init_copy_envp(&copy_envp, envp);

//     while (1)
//     {
//         input = readline("minishell>>> ");
//         if (!input)
//         {
//             break;
//         }
//         if (*input)
//         {
//             add_history(input);
//             // Update input after processing using the refactored function
//             input = handle_dollar_signe(input, copy_envp);
//             printf("%s\n", input);
//         }
//         free(input);
//     }

//     // Free the linked list and clean up
//     free_list(copy_envp);

//     return 0;
// }