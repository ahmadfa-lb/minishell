/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:17:32 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/02 03:16:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_unset(t_env **head, const char *key)
// {
// 	t_env *current;
// 	t_env *previous;

// 	current = *head;
// 	previous = NULL;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 		{
// 			if (previous) 
// 				previous->next = current->next;
// 			else
// 				*head = current->next;
// 			free(current->key);
// 			free(current->value);
// 			free(current);
// 			return (0);
// 		}
// 		previous = current;
// 		current = current->next;
// 	}
// 	return (-1);
// }

void remove_env_node(t_env **head, t_env *current, t_env *previous)
{
    if (previous)
        previous->next = current->next;
    else
        *head = current->next;

    free(current->key);
    free(current->value);
    free(current);
}

int find_and_remove_key(t_env **head, const char *key)
{
    t_env *current = *head;
    t_env *previous = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            remove_env_node(head, current, previous);
            return 0; // Key found and removed
        }
        previous = current;
        current = current->next;
    }
    
    return -1; // Key not found
}

int ft_unset(t_env **head, char **keys)
{
    int status = 0;
    int i = 1;

    while (keys[i])
    {
        if (find_and_remove_key(head, keys[i]) == -1)
        {
            printf("unset: `%s': not found\n", keys[i]);
            status = -1;
        }
        i++; // Move to the next key in the array
    }

    return status;
}

