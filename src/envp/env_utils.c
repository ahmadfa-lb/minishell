/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:39:00 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/20 05:41:34 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_envp_list(t_envp_node *head)
{
	t_envp_node *current;
	
	while (head)
	{
		current = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = current;
	}
}

char	*get_env(t_envp_node *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0) 
			return head->value;
		head = head->next;
	}
	return NULL;
}

int	set_env(t_envp_node **head, const char *key, const char *value)
{
	t_envp_node *current;
	t_envp_node *new_node;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0) {
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	new_node = create_envp_node((char *)key, (char *)value);
	if (!new_node)
		return (-1);
	new_node->next = *head;
	*head = new_node;
	return (0);
}

int	unset_env(t_envp_node **head, const char *key)
{
	t_envp_node *current;
	t_envp_node *previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous) 
				previous->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (-1);
}

// // Function to print the entire env list
// void print_env_list(t_envp_node *head) {
//     t_envp_node *current = head;
//     while (current) {
//         printf("%s=%s\n", current->key, current->value);
//         current = current->next;
//     }
// }

// int main(int argc, char **argv, char **envp) {
//     // Copy the envp to a linked list
//     t_envp_node *envp_list = copy_envp_to_list(envp);
    
//     // Check if the list was created successfully
//     if (!envp_list) {
//         fprintf(stderr, "Error: Failed to copy envp to the linked list\n");
//         return 1;
//     }

//     // Test get_env()
//     char *path_value = get_env(envp_list, "PATH");
//     if (path_value) {
//         printf("GET: PATH = %s\n", path_value);
//     } else {
//         printf("GET: PATH not found\n");
//     }

//     // Test set_env()
//     printf("\nSetting NEW_VAR to 'new_value'...\n");
//     set_env(&envp_list, "NEW_VAR", "new_value");
//     printf("GET: NEW_VAR = %s\n", get_env(envp_list, "NEW_VAR"));

//     // Test update existing variable using set_env()
//     printf("\nUpdating NEW_VAR to 'updated_value'...\n");
//     set_env(&envp_list, "NEW_VAR", "updated_value");
//     printf("GET: NEW_VAR = %s\n", get_env(envp_list, "NEW_VAR"));

//     // Print all environment variables after setting new ones
//     printf("\nEnvironment Variables after set_env:\n");
//     print_env_list(envp_list);

//     // Test unset_env()
//     printf("\nUnsetting NEW_VAR...\n");
//     unset_env(&envp_list, "NEW_VAR");
//     if (!get_env(envp_list, "NEW_VAR")) {
//         printf("GET: NEW_VAR successfully removed\n");
//     } else {
//         printf("GET: Failed to remove NEW_VAR\n");
//     }

//     // Print all environment variables after unsetting
//     printf("\nEnvironment Variables after unset_env:\n");
//     print_env_list(envp_list);

//     // Free the linked list
//     free_envp_list(envp_list);

//     return 0;
// }