/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:39:00 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/31 05:17:15 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp_list(t_env *head)
{
	t_env *current;
	
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
			return head->value;
		head = head->next;
	}
	return NULL;
}

int	set_env(t_env **head, const char *key, const char *value, int hidden)
{
	t_env *current;
	t_env *new_node;

	current = *head;
	if (!value)
	{
		value = ft_strdup("");
	}
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0) {
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	new_node = create_envp_node((char *)key, (char *)value, hidden);
	if (!new_node)
		return (-1);
	new_node->next = *head;
	*head = new_node;
	return (0);
}

