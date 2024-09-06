/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:26:09 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/05 19:14:54 by afarachi         ###   ########.fr       */
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

void	free_parser_list(t_cmd *parser_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = parser_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->tokens_list)
			free_tokens(current->tokens_list);
		if (current->list_redirectors)
			free_tokens(current->list_redirectors);
		free(current);
		current = next;
	}
}

void	free_tokens(t_list_tokens *tokens)
{
	t_list_tokens	*next;

	if (!tokens)
		return ;
	while (tokens)
	{
		next = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd_list)
		free_parser_list(data->cmd_list);
	if (data->env_list)
		free_envp_list(data->env_list);
	if (data->first_tokens_list)
		free_tokens(data->first_tokens_list);
	if (data->user_input)
		free(data->user_input);
	data->cmd_list = NULL;
	data->env_list = NULL;
	data->first_tokens_list = NULL;
	data->env_array = NULL;
}
