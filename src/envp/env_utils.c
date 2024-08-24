/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:39:00 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/23 11:35:56 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp_list(t_env *head)
{
	t_env	*current;

	while (head)
	{
		current = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = current;
	}
}

char	*get_env(t_env *head, const char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

int	set_env(t_env **head, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
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

int	unset_env(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*previous;

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
