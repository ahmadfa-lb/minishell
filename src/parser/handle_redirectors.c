/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/30 13:44:04 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_parser_list(t_cmd *parser_list)
{
    t_cmd *current;
    t_cmd *next;

    current = parser_list;
    while (current != NULL)
    {
        next = current->next;
        free_tokens(current->tokens_list);
        free_tokens(current->list_redirectors);
        free(current);
        current = next;
    }
}

t_list_tokens *get_last(t_list_tokens *head)
{
    while (head && head->next && head->next->type != TOKEN_PIPE)
        head = head->next;
    return head;
}
int	ft_lstsize1(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// void split_tokens_by_pipe(t_list_tokens *tokens_list, t_cmd **cmd_list)
// {
//     t_list_tokens *tmp = tokens_list;
//     t_list_tokens *head;
//     t_list_tokens *last;

//     while (tmp)
//     {
//         head = tmp;
//         last = get_last(head);
//         if (last->next)
//         {   
//             tmp = last->next->next;
//         }
//         else
//             tmp = last->next;
//         t_cmd *new_cmd = create_cmd_node(head, last);
//         append_cmd_node(cmd_list, new_cmd, head, last);
//     }
// }

void split_tokens_by_pipe(t_data *data, t_cmd **cmd_list)
{
    t_list_tokens *tmp = data->first_tokens_list;
    t_list_tokens *head;
    t_list_tokens *last;

    while (tmp)
    {
        head = tmp;
        last = get_last(head);
        if (last->next)
        {   
            tmp = last->next->next;
        }
        else
            tmp = last->next;
        t_cmd *new_cmd = create_cmd_node(head, last);
        append_cmd_node(cmd_list, new_cmd, head, last);
    }
    data->nb_pipes = ft_lstsize1(*cmd_list) - 1;
}

// Parse all redirections for each command in the command list
void	parse_all_redirections(t_cmd *cmd_list)
{
    t_cmd			*current_cmd;
	t_list_tokens	*token;
	t_list_tokens	*file_token;
	t_list_tokens	*redir_node;
	t_list_tokens	*file_node;
	
	current_cmd = cmd_list;
    while (current_cmd)
	{
        token = current_cmd->tokens_list;
        while (token)
		{
            if (is_redirector(token->type)) {
                file_token = token->next;
                // Create new nodes for the redirector and its associated file
				redir_node = create_token_node(token->type, NO_QUOTE, token->value, false);
				file_node = create_token_node(file_token->type, file_token->quote_type, file_token->value, file_token->space);
	            // Append them to the redirectors list in the current command node
	            append_token(&(current_cmd->list_redirectors), redir_node);
	            append_token(&(current_cmd->list_redirectors), file_node);
	            // Remove the redirector and its associated file from the tokens list
	            token = remove_token(&(current_cmd->tokens_list), token);     // Remove redirector
	            token = remove_token(&(current_cmd->tokens_list), file_token); // Remove associated file
	        } else 
	            token = token->next;
	    }
	    // Move to the next command node
	    current_cmd = current_cmd->next;
	}
}


