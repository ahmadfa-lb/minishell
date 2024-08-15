/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:39:00 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/15 21:42:32 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_value
{
    char *value;
    struct s_value *next;
} t_value;

typedef struct s_env
{
    char *key;
    t_value *value_head;
    struct s_env *next;
} t_env;

t_value *new_value_node(char *value)
{
    t_value *node;

    node = (t_value *)malloc(sizeof(t_value));
    if (!node)
        return (NULL);
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = ft_strdup("");
    node->next = NULL;
    return (node);
}

void add_value_node(t_value **value_head, char *value)
{
    t_value *new_value;
    t_value *temp;

    new_value = new_value_node(value);
    if (!*value_head)
    {
        *value_head = new_value;
    }
    else
    {
        temp = *value_head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_value;
    }
}

t_env *create_node(char *key, char *value)
{
    t_env *res;
    int i;
    char **splited_values;

    res = malloc(sizeof(t_env));
    i = 0;
    if (!res)
    {
        perror("Failed to allocate memory for new node");
        return (NULL);
    }
    res->key = ft_strdup(key);
    res->value_head = NULL; // Initialize value_head to NULL
    splited_values = ft_split(value, ':');
    while (splited_values[i])
    {
        add_value_node(&(res->value_head), splited_values[i]);
        i++;
    }
    res->next = NULL;
    return (res);
}

void append_node(t_env **head, char *key, char *value)
{
    t_env *new_node;
    t_env *current;

    new_node = create_node(key, value);
    if (!new_node)
        return;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
// free functions
void free_value_list(t_value *value_head)
{
    t_value *current_value;
    t_value *next_value;

    current_value = value_head;
    while (current_value)
    {
        next_value = current_value->next;
        free(current_value->value);
        free(current_value);
        current_value = next_value;
    }
}

void free_list(t_env *env_head)
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
        free_value_list(current_env->value_head);
        // Free the env node itself
        free(current_env);
        current_env = next_env;
    }
}

void init_copy_envp(t_env **head, char **envp)
{
    char **copy_env;
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        copy_env = ft_split_env(envp[i], '=');
        if (copy_env)
        {
            if (copy_env[0] && copy_env[1])
                append_node(head, copy_env[0], copy_env[1]);
            else if (copy_env[0] && !copy_env[1])
                append_node(head, copy_env[0], ft_strdup(""));
            free_tab(copy_env);
        }
        i++;
    }
}
// for testing

void print_list(t_env *env_head)
{
    t_env *current_env;
    t_value *current_value;

    current_env = env_head;
    while (current_env)
    {
        // Print the key
        printf("Key: %s\n", current_env->key);
        // Print the values
        current_value = current_env->value_head;
        printf("Values: ");
        while (current_value)
        {
            printf("%s", current_value->value);
            if (current_value->next)
                printf(", ");
            current_value = current_value->next;
        }
        printf("\n\n"); // Print a newline between entries
        // Move to the next env node
        current_env = current_env->next;
    }
}

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