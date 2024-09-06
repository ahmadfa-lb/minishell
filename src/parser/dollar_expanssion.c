/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expanssion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/06 14:37:09 by afarachi         ###   ########.fr       */
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

// t_list_tokens	*dollar_expansion(t_list_tokens *tokens, t_data *data)
// {
// 	t_list_tokens	*current_token;
// 	t_list_tokens	*previous_token;
// 	t_list_tokens	*new_token;
// 	t_list_tokens	*temp;
// 	char			*result;
// 	char			**split_strings;
// 	char			*test;
// 	int				array_length;
// 	int				i;

// 	previous_token = NULL;
// 	split_strings = NULL;
// 	result = NULL;
// 	array_length = 0;
// 	i = 0;
// 	current_token = tokens;
// 	while (current_token)
// 	{
// 		if (previous_token
// 			&& previous_token->type == TOKEN_HEREDOC && current_token->value)
// 		{
// 			previous_token = current_token;
// 			current_token = current_token->next;
// 			continue ;
// 		}
// 		if (current_token->value
// 			&& ft_strchr(current_token->value, '$')
// 			&& current_token->quote_type != SINGLE_QUOTE)
// 		{
// 			result = handle_dollar_sign(current_token->value,
// 					data->env_list, data->exit_status);
// 			if (current_token->quote_type == NO_QUOTE)
// 			{
// 				split_strings = ft_split(result, ' ');
// 				if (!split_strings || !*split_strings)
// 				{
// 					temp = current_token->next;
// 					ft_free_node(&data->first_tokens_list, current_token);
// 					current_token = temp;
// 					continue ;
// 				}
// 				else if (split_strings[0] && split_strings[1] == NULL)
// 				{
// 					//free(current_token->value);
// 					printf("Allocating memory for token1: %s\n", current_token->value);
// 					current_token->value = split_strings[0];
// 				}
// 				else
// 				{
// 					printf("Allocating memory for token2: %s\n", current_token->value);
// 					free(current_token->value);
// 					current_token->value = ft_strdup(split_strings[0]);
// 					array_length = get_string_array_length(split_strings);
// 					i = 1;
// 					while (i < array_length)
// 					{
// 						test = ft_strdup(split_strings[i]);
// 						new_token = create_token_node(current_token->type,
// 								current_token->quote_type, test, 1);
// 						insert_at(&data->first_tokens_list,
// 							current_token, new_token);
// 						current_token = current_token->next;
// 						free(test);
// 						i++;
// 					}
// 					(free(result), free_args(split_strings));
// 				}
// 			}
// 			else
// 			{
// 				printf("Allocating memory for token3: %s\n", current_token->value);
// 				free(current_token->value);
// 				current_token->value = ft_strdup(result);
// 			}
// 		}
// 		previous_token = current_token;
// 		current_token = current_token->next;
// 	}
// 	return (free(result), free(split_strings), tokens);
// }

static bool	should_skip_token(t_list_tokens *previous_token,
	t_list_tokens *current_token)
{
	return (previous_token && previous_token->type == TOKEN_HEREDOC
		&& current_token->value);
}

static void	handle_quoted_token(t_list_tokens *current_token, char *result)
{
	free(current_token->value);
	current_token->value = ft_strdup(result);
}

static void	insert_split_tokens(t_data *data, t_list_tokens *current_token,
	char **split_strings, int array_length)
{
	t_list_tokens	*new_token;
	int				i;

	i = 1;
	while (i < array_length)
	{
		new_token = create_token_node(current_token->type,
				current_token->quote_type, ft_strdup(split_strings[i]), 1);
		insert_at(&data->first_tokens_list, current_token, new_token);
		current_token = current_token->next;
		i++;
	}
}

static bool	handle_non_quoted_token(t_data *data, t_list_tokens *current_token,
	char *result)
{
	char			**split_strings;
	int				array_length;

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
			return ;
	}
	else
		handle_quoted_token(current_token, result);
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
