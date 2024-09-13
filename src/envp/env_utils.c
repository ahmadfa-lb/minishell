/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:39:00 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/13 15:05:53 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increment_shell_level(t_env **env_list, int is_hidden)
{
	char	*shell_level_str;
	char	*new_shell_level_str;
	int		shell_level;

	shell_level_str = get_env(*env_list, "SHLVL");
	if (shell_level_str == NULL)
		shell_level = 1;
	else
		shell_level = ft_atoi(shell_level_str);
	shell_level++;
	new_shell_level_str = ft_itoa(shell_level);
	set_env(env_list, "SHLVL", new_shell_level_str, is_hidden);
	free(new_shell_level_str);
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

int	set_env(t_env **head, const char *key, const char *value, int hidden)
{
	t_env	*current;
	t_env	*new_node;

	current = *head;
	if (!value)
		value = ft_strdup("");
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			current->hidden = hidden;
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

void	setup_initial_environment(t_env **env_list)
{
	char	current_working_dir[1024];

	if (!*env_list)
		return ;
	if (get_env(*env_list, "PWD"))
		return ;
	if (getcwd(current_working_dir, sizeof(current_working_dir)))
		set_env(env_list, "PWD", current_working_dir, 0);
	else
		perror("minishell: getcwd");
	set_env(env_list, "OLDPWD", NULL, 1);
	set_env(env_list, "SHLVL", "1", 0);
}
