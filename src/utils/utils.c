/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:16:46 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/05 19:49:58 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_skip_whitespace(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

int	ft_is_delimiter(char c)
{
	if (c == '$')
	{
		return (1);
	}
	if (c == '|' || c == '>' || c == '<')
	{
		return (1);
	}
	if (c == '\'' || c == '"')
	{
		return (1);
	}
	return (0);
}
int	is_redirector(int type)
{
	return (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_REDIRECT_OUT
		||type == TOKEN_APPEND);
}

int	ft_cmd_lstsize(t_cmd *lst)
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

int	get_string_array_length(char **string)
{
	int	length;

	length = 0;
	if (string == NULL)
		return (0);
	while (string[length] != NULL)
		length++;
	return (length);
}