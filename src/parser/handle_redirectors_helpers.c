/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirectors_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:17:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/02 15:17:05 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_redirector(int type)
{
    return (type == TOKEN_REDIRECT_IN || 
            type == TOKEN_HEREDOC || 
            type == TOKEN_REDIRECT_OUT || 
            type == TOKEN_APPEND);
}


// Remove a token from the token list
t_list_tokens	*remove_token(t_list_tokens **tokens_list, t_list_tokens *token)
{
	t_list_tokens *current;

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
	}
	return (current ? current->next : NULL);
}

void append_cmd_tokens(t_cmd **cmd_list, t_list_tokens *head, t_list_tokens *last)
{
    if (head == last)
    {
        (*cmd_list)->tokens_list = create_token_node(head->type, head->quote_type, ft_strdup(head->value), head->space);
        return ;
    }
    while (head != last->next)
    {
        t_list_tokens *new_node =  create_token_node(head->type, head->quote_type, ft_strdup(head->value), head->space);
        append_token(&(*cmd_list)->tokens_list, new_node);
        head = head->next;
    }
}

// void append_cmd_tokens(t_cmd **cmd_list, t_list_tokens *head, t_list_tokens *last)
// {
//     if (head == last)
//     {
//         if (head->value)
//         {
//             (*cmd_list)->tokens_list = create_token_node(head->type, head->quote_type, ft_strdup(head->value), head->space);
//         }
//         else
//         {
//             (*cmd_list)->tokens_list = create_token_node(head->type, head->quote_type, NULL, head->space);
//         }
//         return;
//     }
//     while (head != last->next)
//     {
//         if (head->value)
//         {
//             t_list_tokens *new_node = create_token_node(head->type, head->quote_type, ft_strdup(head->value), head->space);
//             append_token(&(*cmd_list)->tokens_list, new_node);
//         }
//         else
//         {
//             t_list_tokens *new_node = create_token_node(head->type, head->quote_type, NULL, head->space);
//             append_token(&(*cmd_list)->tokens_list, new_node);
//         }
//         head = head->next;
//     }
// }

void append_cmd_node(t_cmd **cmd_list, t_cmd *new_node, t_list_tokens *head, t_list_tokens *last) {
    if (!*cmd_list)
    {
        (*cmd_list) = new_node;
        append_cmd_tokens(cmd_list, head, last);
        return ;
    }
    t_cmd *curr = *cmd_list;
    while (curr->next) 
    {
        curr = curr->next;
    }
    curr->next = new_node;
    append_cmd_tokens(&(curr->next), head, last);
}

// Create a new command node
t_cmd *create_cmd_node() {
    t_cmd *new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd) return NULL; // Handle malloc failure

    new_cmd->tokens_list = NULL;
    new_cmd->list_redirectors = NULL;
    new_cmd->prev = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}