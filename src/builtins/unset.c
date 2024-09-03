/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:17:32 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/03 23:34:55 by mouhamad_kr      ###   ########.fr       */
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

void find_and_remove_key(t_env **head, const char *key)
{
    t_env *current = *head;
    t_env *previous = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            remove_env_node(head, current, previous);
            return ; // Key found and removed
        }
        previous = current;
        current = current->next;
    }
    
    return ; // Key not found
}

int ft_unset(t_env **head, char **keys)
{
    int status = 0;
    int i = 1;
    
    while (keys[i])
    {
        if (!check_key(keys[i]))
        {
            printf("unset: `%s': not a valid identifier\n", keys[i]);
            status = 1;
        }
        find_and_remove_key(head, keys[i]);
        i++; // Move to the next key in the array
    }

    return status;
}

