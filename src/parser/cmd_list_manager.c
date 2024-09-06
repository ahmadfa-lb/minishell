/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:17:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 14:37:49 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list_tokens	*remove_token(t_list_tokens **tokens_list, t_list_tokens *token)
{
	t_list_tokens	*current;

	current = *tokens_list;
	if (current == token)
	{
		*tokens_list = token->next;
		free(token->value);
		free(token);
		return (*tokens_list);
	}
	while (current && current->next != token)
		current = current->next;
	if (current && current->next == token)
	{
		current->next = token->next;
		free(token->value);
		free(token);
		return (current->next);
	}
	else
		return (NULL);
}

void	append_cmd_tokens(t_cmd **cmd_list, t_list_tokens *head,
	t_list_tokens *last)
{
	t_list_tokens	*new_node;
	char			*str_val1;
	char			*str_val2;

	if (head == last)
	{
		str_val1 = ft_strdup(head->value);
		(*cmd_list)->tokens_list = create_token_node(head->type,
				head->quote_type, str_val1, head->space);
		free(str_val1);
		return ;
	}
	while (head != last->next)
	{
		str_val2 = ft_strdup(head->value);
		new_node = create_token_node(head->type,
				head->quote_type, str_val2, head->space);
		append_token(&(*cmd_list)->tokens_list, new_node);
		head = head->next;
		free(str_val2);
	}
}

void	append_cmd_node(t_cmd **cmd_list, t_cmd *new_node, t_list_tokens *head,
	t_list_tokens *last)
{
	t_cmd	*curr;

	if (!*cmd_list)
	{
		(*cmd_list) = new_node;
		append_cmd_tokens(cmd_list, head, last);
		return ;
	}
	curr = *cmd_list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
	append_cmd_tokens(&(curr->next), head, last);
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->tokens_list = NULL;
	new_cmd->list_redirectors = NULL;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
