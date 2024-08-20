/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:56:10 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/20 06:07:52 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp_node	*create_envp_node(char *key, char *value)
{
	t_envp_node	*new_node;

	new_node = (t_envp_node *)malloc(sizeof(t_envp_node));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}	
void	split_envp(char *envp_str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp_str, '=');
	if (equal_sign) {
		*key = ft_strndup(envp_str, equal_sign - envp_str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(envp_str);
		*value = NULL;
	}
}

t_envp_node	*copy_envp_to_list(char **envp)
{
	t_envp_node	*head;
	t_envp_node	*current;
	t_envp_node	*new_node;
	char		*key;
	char		*value;
		
	head = NULL;
	current = NULL;
	while (*envp)
	{
		split_envp(*envp, &key, &value);
		new_node = create_envp_node(key, value);
		free(key);
		free(value);
		if (!new_node)
		{
			while (head) 
			{
		    	current = head->next;
		    	free(head->key);
		    	free(head->value);
		    	free(head);
		    	head = current;
			}
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		envp++;
	}
	return (head);
}