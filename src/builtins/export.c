/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:50:50 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/28 20:51:50 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void append_env_node(t_env **head, char *key, char *value)
{
    t_env *current;
    t_env *new_node = create_envp_node(key, value);

    // If the list is empty, the new node becomes the head
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    // Traverse to the last node
    current = *head;
    while (current->next != NULL)
        current = current->next;

    // Append the new node at the end
    current->next = new_node;
}
void remove_quotes_from_str(char *str)
{
    char *src;
    char *dst;
    char quote;

    quote = 0;
    src = str;
    dst = str;
    while (*src)
    {
        if (!quote && (*src == '\'' || *src == '\"'))
            quote = *src;
        else if (quote && *src == quote)
            quote = 0;
        else
        {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}
int check_key(char *key)
{
    int i = 0;

    if (!ft_isalpha(key[0]) && key[0] != '_')
    {
        return (0);
    }
    i++;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
        {
            return (0);
        }
        i++;
    }

    return (1);
}

int update_env_value(t_env *head, const char *key, const char *new_value)
{
    t_env *current = head;

    // Traverse the list to find the node with the matching key
    while (current)
    {
        if (strcmp(current->key, key) == 0) // If the key matches
        {
            free(current->value);               // Free the old value
            current->value = strdup(new_value); // Update with the new value

            if (!current->value)
                return -1; // Memory allocation failure

            return 0; // Success
        }
        current = current->next;
    }
    return -1; // Key not found
}

void handle_export(t_env **env_list, char *input)
{
    char **args;

    args = ft_split(input, '=');
    if (!args[1])
    {
        args[1] = ft_strdup("");
    }
    if (check_key(args[0]) == 0)
    {
        return;
    }

    if (args[0] && update_env_value(*env_list, args[0], args[1]) == -1)
    {
        remove_quotes_from_str(args[1]);
        append_env_node(env_list, args[0], args[1]);
    }
}