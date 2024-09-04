/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:56:10 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 08:27:20 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_envp_node(char *key, char *value, int hidden)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->hidden = hidden;
	new_node->next = NULL;
	return (new_node);
}

void	split_envp(char *envp_str, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(envp_str, '=');
	if (equal_sign)
	{
		*key = ft_strndup(envp_str, equal_sign - envp_str);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(envp_str);
		*value = NULL;
	}
}

t_env	*create_envp_list_node(char *envp_str, int hidden)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	split_envp(envp_str, &key, &value);
	new_node = create_envp_node(key, value, hidden);
	free(key);
	free(value);
	return (new_node);
}

void	add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}
// void add_uid_to_envp_list(t_env *head)
// {
// 	char *UID;
// 	pid_t uid;
// 	int res;

// 	uid = ft_getuid();
// 	UID = ft_itoa((int)uid);

// 	res = set_env(&head, "UID", UID);
// 	if (res != 0)
//     {
//         free_envp_list(head);
//         return NULL;
//     }
// 	free(res);
// 	free(UID);
// }

t_env	*init_copy_envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	char	*uid_str;
	pid_t	uid;

	uid = ft_getuid();
	uid_str = ft_itoa((int)uid);
	head = NULL;
	current = NULL;
	while (*envp)
	{
		new_node = create_envp_list_node(*envp, 0);
		if (!new_node)
			free_envp_list(head);
		add_node_to_envp_list(&head, &current, new_node);
		envp++;
	}
	if (set_env(&head, "UID", uid_str, 2) != 0)
	{
		free_envp_list(head);
		return (NULL);
	}
	free(uid_str);
	return (head);
}
