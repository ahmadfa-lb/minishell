/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expanssion_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/06 19:55:52 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	insert_at(t_list_tokens **tokens, t_list_tokens *current,
	t_list_tokens *new)
{
	t_list_tokens	*tmp;

	if (!tokens || !*tokens || !current)
		return ;
	tmp = *tokens;
	while (tmp != current)
		tmp = tmp->next;
	if (!tmp)
		return ;
	new->next = tmp->next;
	tmp->next = new;
}

bool	should_skip_token(t_list_tokens *previous_token,
	t_list_tokens *current_token)
{
	return (previous_token && previous_token->type == TOKEN_HEREDOC
		&& current_token->value);
}

void	handle_quoted_token(t_list_tokens *current_token, char *result)
{
	free(current_token->value);
	current_token->value = ft_strdup(result);
}
