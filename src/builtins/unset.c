/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:17:32 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 19:00:22 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_node(t_env **head, t_env *current, t_env *previous)
{
	if (previous)
		previous->next = current->next;
	else
		*head = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

void	find_and_remove_key(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			remove_env_node(head, current, previous);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_env **head, char **keys)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	while (keys[i])
	{
		if (!check_key(keys[i]))
		{
			printf("unset: `%s': not a valid identifier\n", keys[i]);
			status = 1;
		}
		find_and_remove_key(head, keys[i]);
		i++;
	}
	return (status);
}
