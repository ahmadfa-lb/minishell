/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:24:29 by odib              #+#    #+#             */
/*   Updated: 2024/08/30 21:44:05 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	append_env_node(t_env **head, char *key, char *value)
//{
//	t_env	*current;
//	t_env	*new_node;

//	new_node = create_envp_node(key, value, 0);
//	// If the list is empty, the new node becomes the head
//	if (*head == NULL)
//	{
//		*head = new_node;
//		return ;
//	}
//	// Traverse to the last node
//	current = *head;
//	while (current->next != NULL)
//		current = current->next;
//	// Append the new node at the end
//	current->next = new_node;
//}
void swap_nodes(t_env *a, t_env *b)
{
    char *temp_key = a->key;
    char *temp_value = a->value;

    a->key = b->key;
    a->value = b->value;

    b->key = temp_key;
    b->value = temp_value;
}


void sort_env_list(t_env *head)
{
    int swapped;
    t_env *ptr1;
    t_env *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->key, ptr1->next->key) > 0)
            {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void	remove_quotes_from_str(char *str)
{
	char	*src;
	char	*dst;
	char	quote;

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

int	check_key(char *key)
{
	int	i;

	i = 0;
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

void	print_sorted_env_list(t_env *head)
{
	t_env	*current;

	current = head;
	sort_env_list(current);
	while (current)
	{
		printf("%s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

// int	update_env_value(t_env *head, const char *key, const char *new_value)
//{
//	t_env	*current;

//	current = head;
//	// Traverse the list to find the node with the matching key
//	while (current)
//	{
//		if (strcmp(current->key, key) == 0) // If the key matches
//		{
//			free(current->value);               // Free the old value
//			current->value = strdup(new_value); // Update with the new value
//			if (!current->value)
//				return (-1); // Memory allocation failure
//			return (0);      // Success
//		}
//		current = current->next;
//	}
//	return (-1); // Key not found
//}

int	is_input_null(char **input)
{
	return (input[1] == NULL);
}

int	is_key_invalid(char *key)
{
	if (check_key(key) == 0)
	{
		printf("Invalid key: %s\n", key); // Debugging
		return (1);
	}
	return (0);
}

void	free_resources(char *key, char *value)
{
	free(value);
	free(key);
}

int	handle_export(t_env **env_list, char **input)
{
	char *key;
	char *value;
	int i;

	i = 1;
	if (is_input_null(input))
	{
		print_sorted_env_list(*env_list);
		return (0);
	}
	while (input[i])
	{
		split_envp(input[i], &key, &value);
		if (is_key_invalid(key))
		{
			free_resources(key, value);
			i++;
			continue;
		}
		if (!value)
			set_env(env_list, key, value, 1);
		else
			set_env(env_list, key, value, 0);
		free_resources(key, value);
		i++;
	}
	return (0);
}

