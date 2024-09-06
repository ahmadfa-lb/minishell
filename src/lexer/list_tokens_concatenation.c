/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tokens_concatenation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 06:23:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/05 10:32:45 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_token_join(t_list_tokens **tmp, t_list_tokens **to_del)
{
	(*to_del) = (*tmp)->next;
	if (ft_strlen((*tmp)->value) == 1 && !ft_strncmp((*tmp)->value, "$", 1)
		&& (*tmp)->quote_type == NO_QUOTE)
	{
		free((*tmp)->value);
		(*tmp)->value = ft_strdup((*tmp)->next->value);
	}
	else
		(*tmp)->value = ft_strjoin((*tmp)->value, (*tmp)->next->value);
}

void	ft_free_node(t_list_tokens **tokens, t_list_tokens *del)
{
	t_list_tokens	*tmp;

	if (!tokens || !*tokens)
		return ;
	if (*tokens == del)
	{
		*tokens = (*tokens)->next;
		if (del->value)
			free (del->value);
		free(del);
		del = NULL;
		return ;
	}
	tmp = *tokens;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	if (del->value)
		free(del->value);
	free(del);
	del = NULL;
}

void	concate_nodes(t_list_tokens **list_token)
{
	t_list_tokens	*tmp;
	t_list_tokens	*del;

	del = NULL;
	if (!list_token || !*list_token)
		return ;
	tmp = *list_token;
	while (tmp && tmp->next)
	{
		if (tmp->space == 0)
		{
			ft_token_join(&tmp, &del);
			if (tmp->next->space == 1)
				tmp = tmp->next->next;
			ft_free_node(list_token, del);
		}
		else
			tmp = tmp->next;
	}
}
