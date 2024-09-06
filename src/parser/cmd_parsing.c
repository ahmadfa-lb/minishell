/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 14:37:36 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list_tokens	*get_last(t_list_tokens *head)
{
	while (head && head->next && head->next->type != TOKEN_PIPE)
		head = head->next;
	return (head);
}

void	split_tokens_by_pipe(t_data *data, t_cmd **cmd_list)
{
	t_list_tokens	*tmp;
	t_list_tokens	*head;
	t_list_tokens	*last;
	t_cmd			*new_cmd;

	tmp = data->first_tokens_list;
	while (tmp)
	{
		head = tmp;
		last = get_last(head);
		if (last->next)
			tmp = last->next->next;
		else
			tmp = last->next;
		new_cmd = create_cmd_node();
		append_cmd_node(cmd_list, new_cmd, head, last);
	}
	data->nb_pipes = ft_cmd_lstsize(*cmd_list) - 1;
}

void	append_redirection_tokens(t_cmd *cmd, t_list_tokens *token)
{
	t_list_tokens	*redir_node;
	t_list_tokens	*file_node;
	t_list_tokens	*file_token;

	file_token = token->next;
	redir_node = create_token_node(token->type, NO_QUOTE, token->value, false);
	file_node = create_token_node(file_token->type, file_token->quote_type,
			file_token->value, file_token->space);
	append_token(&(cmd->list_redirectors), redir_node);
	append_token(&(cmd->list_redirectors), file_node);
}

void	process_redirections(t_cmd *cmd, t_list_tokens **token)
{
	t_list_tokens	*file_token;

	file_token = (*token)->next;
	append_redirection_tokens(cmd, *token);
	*token = remove_token(&(cmd->tokens_list), *token);
	*token = remove_token(&(cmd->tokens_list), file_token);
}

void	parse_all_redirections(t_cmd *cmd_list)
{
	t_cmd			*current_cmd;
	t_list_tokens	*token;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		token = current_cmd->tokens_list;
		while (token)
		{
			if (is_redirector(token->type))
				process_redirections(current_cmd, &token);
			else
				token = token->next;
		}
		current_cmd = current_cmd->next;
	}
}
