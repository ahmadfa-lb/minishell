/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:24:29 by odib              #+#    #+#             */
/*   Updated: 2024/09/08 12:17:43 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (!quote && (*src == '\"'))
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

void	print_sorted_env_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->value && *current->value != '\0')
			printf("export %s=%s\n", current->key, current->value);
		else
			printf("export %s\n", current->key);
		current = current->next;
	}
}

int	is_input_null(char **input)
{
	return (input[1] == NULL);
}

int	is_key_invalid(char *key, char *value, char *input)
{
	if (check_key(key) == 0)
	{
		if (!value)
			printf("export: `%s': not a valid identifier\n", input);
		else
			printf("export: `%s=%s': not a valid identifier\n", key, value);
		return (1);
	}
	return (0);
}

int	ft_export(t_env **env_list, char **input)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (is_input_null(input))
		return (print_sorted_env_list(*env_list), 0);
	while (input[i])
	{
		split_envp(input[i], &key, &value);
		if (is_key_invalid(key, value, input[i]))
		{
			(free(key), free(value));
			i++;
			continue ;
		}
		if (!value)
			set_env(env_list, key, NULL, 1);
		else
			set_env(env_list, key, value, 0);
		(free(key), free(value));
		i++;
	}
	return (0);
}
