/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/04 10:30:44 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_normal_variable(char *input, int *i, char **result, t_env *env)
{
	int start;
	int end;
	char *sub_env;
	char *env_value;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_' || input[*i] == '\0'))
		(*i)++;

	end = *i;
	if (start != end)
	{
		sub_env = ft_substr(input, start, end - start);
		env_value = get_env(env, sub_env);
		if (env_value)
			*result = ft_strjoin(*result, env_value);
		free(sub_env);
	}
	else
	{
		*result = ft_strjoin(*result, " ");
	}
}

// void handle_normal_variable(char *input, int *i, char **result, t_env *env)
// {
//     int start;
//     int end;
//     char *sub_env;
//     char *env_value;

//     (*i)++;
//     start = *i;
//     while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
//         (*i)++;
//     end = *i;
//     if (start != end)
//     {
//         sub_env = ft_substr(input, start, end - start);
//         env_value = get_env(env, sub_env);
//         if (env_value)
//         {
//             *result = ft_strjoin(*result, env_value);
//         }
//         else
//         {
//             *result = ft_strjoin(*result, "");  // Append an empty string for non-existing variables
//         }
//         free(sub_env);
//     }
//     else
//     {
//         *result = ft_strjoin(*result, "$");
//     }
// }

void handle_two_dollar(char **result, int *i)
{
	char *num_str;

	num_str = ft_itoa(getpid());
	*result = ft_strjoin(*result, num_str);
	*i += 2;
	free(num_str);
}
void handle_dollarexitstatus(char **result, int exit_status, int *i)
{
	char *string;

	string = ft_itoa(exit_status);
	*result = ft_strjoin(*result, string);
	*i += 2;
	free(string);
}

char *handle_dollar_sign(char *input, t_env *env, int exit_status)
{
	int i;
	char *result;
	char tmp[2];

	i = 0;
	result = ft_strdup("");
	while (i < ft_strlen1(input) && input[i])
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				handle_dollarexitstatus(&result, exit_status, &i);
			else if (input[i + 1] == '$')
				handle_two_dollar(&result, &i);
			else if (ft_isdigit(input[i + 1]))
				i += 2;
			else
				handle_normal_variable(input, &i, &result, env);
		}
		else
		{
			ft_strlcpy(tmp, input + i, 2);
			result = ft_strjoin(result, tmp);
			i++;
		}
	// free(input);
	return (result);
}

// t_list_tokens	*dollar_expansion(t_data *data)
// {
// 	t_list_tokens	*current_token;

// 	current_token = data->first_tokens_list;
// 	while (current_token)
// 	{
// 		if (current_token->value && ft_strchr(current_token->value, '$') &&
// 		 current_token->quote_type != SINGLE_QUOTE)
// 			current_token->value = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 		current_token = current_token->next;
// 	}
// 	return (data->first_tokens_list);
// }

void insert_at(t_list_tokens **tokens, t_list_tokens *current, t_list_tokens *new)
{
	t_list_tokens *tmp;

	if (!tokens || !*tokens || !current)
		return;
	tmp = *tokens;
	while (tmp != current)
		tmp = tmp->next;
	if (!tmp)
		return;
	new->next = tmp->next;
	tmp->next = new;
}

int get_string_array_length(char **string)
{
	int length = 0;

	if (string == NULL)
		return 0;
	while (string[length] != NULL)
		length++;
	return length;
}

// t_list_tokens *dollar_expansion(t_data *data)
// {
// 	t_list_tokens *current_token;
// 	char *result = NULL;
// 	char **split_strings = NULL;
// 	t_list_tokens *new_token;
// 	t_list_tokens *temp;
// 	int array_length = 0;
// 	int i = 0;

// 	current_token = data->first_tokens_list;
// 	while (current_token)
// 	{
// 		if (current_token->value && ft_strchr(current_token->value, '$') && current_token->quote_type != SINGLE_QUOTE)
// 		{
// 			result = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 			split_strings = ft_split(result, ' ');
// 			if (!split_strings || !*split_strings)
// 			{
// 				if (current_token->quote_type == NO_QUOTE ||current_token->value[0] == '"')
// 				{
// 					temp = current_token->next;
// 					ft_free_node(&data->first_tokens_list, current_token);
// 					current_token = temp;
// 					continue;
// 				}
// 				else
// 				{
// 					current_token->value = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 					continue;

// 				}

// 			}
// 			else if (split_strings[0] && split_strings[1] == NULL)
// 			{
// 				current_token->value = split_strings[0];
// 			}
// 			else
// 			{
// 				// free(current_token->value);
// 				current_token->value = ft_strdup(split_strings[0]);
// 				array_length = get_string_array_length(split_strings);
// 				i = 1;
// 				while (i < array_length)
// 				{
// 					char *test = ft_strdup(split_strings[i]);
// 					new_token = create_token_node(current_token->type, current_token->quote_type, test, 1);
// 					append_token(&current_token, new_token);
// 					current_token = current_token->next;
// 					i++;
// 				}
// 				i = 0;
// 				free(result);
// 				while (split_strings[i])
// 				{
// 					free(split_strings[i]);
// 					i++;
// 				}
// 				free(split_strings);
// 			}
// 		}
// 		current_token = current_token->next;
// 	}
// 	return (data->first_tokens_list);
// }

// t_list_tokens *dollar_expansion(t_data *data)
// {
//     t_list_tokens *current_token;
//     t_list_tokens *previous_token = NULL;
//     char *result = NULL;
//     char **split_strings = NULL;
//     t_list_tokens *new_token;
//     t_list_tokens *temp;
//     int array_length = 0;
//     int i = 0;

//     current_token = data->first_tokens_list;
//     while (current_token)
//     {
//         // Check if the current token is a heredoc delimiter
//         if (previous_token && previous_token->type == TOKEN_HEREDOC && current_token->value)
//         {
//             previous_token = current_token;
//             current_token = current_token->next;
//             continue;
//         }

//         if (current_token->value && ft_strchr(current_token->value, '$') && current_token->quote_type != SINGLE_QUOTE)
//         {
//             result = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 			// if (!ft_strncmp(result, current_token->value, ft_strlen(result)))
// 			// {
// 			// 	// current_token->value = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 			// 	current_token = current_token->next;
// 			// 	printf("\n3\n");
// 			// 	continue;
// 			// }
//             split_strings = ft_split(result, ' ');
//             if (!split_strings || !*split_strings)
//             {
//                 if (current_token->quote_type == NO_QUOTE)
//                 {
// 					printf("\n1\n");
//                     temp = current_token->next;
//                     ft_free_node(&data->first_tokens_list, current_token);
//                     current_token = temp;
//                     continue;
//                 }
//                 else
//                 {
// 					printf("\n2\n");
//                     // current_token->value = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);
// 					current_token->value = ft_strdup(" ");

//                     continue;
//                 }
//             }
//             else if (split_strings[0] && split_strings[1] == NULL)
//             {
// 				printf("\n3\n");
//                 current_token->value = split_strings[0];
//             }
//             else
//             {
// 				printf("\n4\n");
//                 current_token->value = ft_strdup(split_strings[0]);
//                 array_length = get_string_array_length(split_strings);
//                 i = 1;
//                 while (i < array_length)
//                 {
//                     char *test = ft_strdup(split_strings[i]);
//                     new_token = create_token_node(current_token->type, current_token->quote_type, test, 1);
//                     insert_at(&data->first_tokens_list, current_token, new_token);
//                     current_token = current_token->next;
//                     i++;
//                 }
//                 i = 0;
//                 free(result);
//                 while (split_strings[i])
//                 {
//                     free(split_strings[i]);
//                     i++;
//                 }
//                 free(split_strings);
//             }
//         }
//         previous_token = current_token;
//         current_token = current_token->next;
//     }
//     return (data->first_tokens_list);
// }

t_list_tokens *dollar_expansion(t_data *data)
{
	t_list_tokens *current_token;
	t_list_tokens *previous_token = NULL;
	char *result = NULL;
	char **split_strings = NULL;
	t_list_tokens *new_token;
	t_list_tokens *temp;
	int array_length = 0;
	int i = 0;

	current_token = data->first_tokens_list;
	while (current_token)
	{
		// Check if the current token is a heredoc delimiter
		if (previous_token && previous_token->type == TOKEN_HEREDOC && current_token->value)
		{
			previous_token = current_token;
			current_token = current_token->next;
			continue;
		}

		if (current_token->value && ft_strchr(current_token->value, '$') && current_token->quote_type != SINGLE_QUOTE)
		{

			result = handle_dollar_sign(current_token->value, data->env_list, data->exit_status);

			// Only split if the token is not quoted
			if (current_token->quote_type == NO_QUOTE)
			{
				if (current_token->quote_type == NO_QUOTE && !current_token->next)
				{
					current_token->value = ft_strdup("$");
				}
				else
				{
					split_strings = ft_split(result, ' ');
					if (!split_strings || !*split_strings)
					{
						// Remove token if empty after expansion
						temp = current_token->next;
						ft_free_node(&data->first_tokens_list, current_token);
						current_token = temp;
						continue;
					}
					else if (split_strings[0] && split_strings[1] == NULL)
					{
						current_token->value = split_strings[0];
					}
					else
					{
						current_token->value = ft_strdup(split_strings[0]);
						array_length = get_string_array_length(split_strings);
						i = 1;
						while (i < array_length)
						{
							new_token = create_token_node(current_token->type, current_token->quote_type, ft_strdup(split_strings[i]), 1);
							insert_at(&data->first_tokens_list, current_token, new_token);
							current_token = current_token->next;
							i++;
						}
						free(result);
						i = 0;
						while (split_strings[i])
						{
							free(split_strings[i]);
							i++;
						}
						free(split_strings);
					}
				}
			}
			else
			{
				// If quoted, just replace the value without splitting
				current_token->value = result;
			}
		}
		previous_token = current_token;
		current_token = current_token->next;
	}
	return (data->first_tokens_list);
}
