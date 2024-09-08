/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expanssion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/08 12:51:49 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	insert_split_tokens(t_data *data, t_list_tokens *current_token,
	char **split_strings, int array_length)
{
	t_list_tokens	*new_token;
	int				i;
	char			*str_value;

	i = 1;
	while (i < array_length)
	{
		str_value = ft_strdup(split_strings[i]);
		new_token = create_token_node(current_token->type,
				current_token->quote_type, str_value, 1);
		insert_at(&data->first_tokens_list, current_token, new_token);
		current_token = current_token->next;
		free(str_value);
		i++;
	}
}

static bool	handle_non_quoted_token(t_data *data, t_list_tokens *current_token,
	char *result)
{
	char			**split_strings;
	int				array_length;

	if (!*result)
	{
		free(current_token->value);
		current_token->value = ft_strdup("");
		return (false);
	}
	split_strings = ft_split(result, ' ');
	if (!split_strings || !*split_strings)
	{
		ft_free_node(&data->first_tokens_list, current_token);
		return (false);
	}
	free(current_token->value);
	current_token->value = ft_strdup(split_strings[0]);
	if (split_strings[1] != NULL)
	{
		array_length = get_string_array_length(split_strings);
		insert_split_tokens(data, current_token, split_strings, array_length);
	}
	free_args(split_strings);
	split_strings = NULL;
	return (true);
}

static void	process_dollar_expansion(t_list_tokens *current_token, t_data *data)
{
	char	*result;

	result = handle_dollar_sign(current_token->value,
			data->env_list, data->exit_status);
	if (current_token->quote_type == NO_QUOTE)
	{
		if (!handle_non_quoted_token(data, current_token, result))
			return (free(result), (void)0);
	}
	else
	{
		handle_quoted_token(current_token, result);
	}
	free(result);
}

t_list_tokens	*dollar_expansion(t_list_tokens *tokens, t_data *data)
{
	t_list_tokens	*current_token;
	t_list_tokens	*previous_token;

	previous_token = NULL;
	current_token = tokens;
	while (current_token)
	{
		if (should_skip_token(previous_token, current_token))
		{
			previous_token = current_token;
			current_token = current_token->next;
			continue ;
		}
		if (current_token->value && ft_strchr(current_token->value, '$')
			&& current_token->quote_type != SINGLE_QUOTE)
		{
			process_dollar_expansion(current_token, data);
		}
		previous_token = current_token;
		current_token = current_token->next;
	}
	return (tokens);
}
